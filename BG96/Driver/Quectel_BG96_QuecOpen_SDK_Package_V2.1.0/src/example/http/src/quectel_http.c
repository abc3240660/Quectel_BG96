/******************************************************************************
*@file    example_http.c
*@brief   Detection of http download. Customer need creat a config file contained download url in efs.
*         For example: efs file path:/datatx/downloadurl.ini 
          download url like as: http://220.180.239.212:8005/matt/update.zip  or http://xtrapath1.izatcloud.net/xtra2.bin 
*  ---------------------------------------------------------------------------
*
*  Copyright (c) 2018 Quectel Technologies, Inc.
*  All Rights Reserved.
*  Confidential and Proprietary - Quectel Technologies, Inc.
*  ---------------------------------------------------------------------------
*******************************************************************************/
#if defined(__EXAMPLE_HTTP__)
/* Standard C headers
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stdarg.h"

#include "qapi_diag.h"
#include "qapi_socket.h"
#include "qapi_dnsc.h"
#include "qapi_dss.h"
#include "qapi_timer.h"
#include "qapi_uart.h"
#include "qapi_fs.h"
#include "qapi_status.h"
#include "qapi_netservices.h"
#include "qapi_httpc.h"

#include "../inc/quectel_http.h"

/*===========================================================================
						   Header file
===========================================================================*/
/*===========================================================================
                             DEFINITION
===========================================================================*/
#define QL_DEF_APN	        "CMNET"
#define DSS_ADDR_INFO_SIZE	5
#define DSS_ADDR_SIZE       16

#define GET_ADDR_INFO_MIN(a, b) ((a) > (b) ? (b) : (a))

/*===========================================================================
                           Global variable
===========================================================================*/


TX_EVENT_FLAGS_GROUP http_signal_handle;

qapi_DSS_Hndl_t http_dss_handle = NULL;	            /* Related to DSS netctrl */
qapi_Net_HTTPc_handle_t  http_hadle = NULL;

static char apn[QUEC_APN_LEN];					/* APN */
static char apn_username[QUEC_APN_USER_LEN];	/* APN username */
static char apn_passwd[QUEC_APN_PASS_LEN];		/* APN password */

#define FILE_PATH "/datatx/downloadfile.bin"
#define URL_PATH "/datatx/downloadurl.ini"

#define TRUE 0
#define FALSE 1
typedef  unsigned char      boolean; 
/* @Note: If netctrl library fail to initialize, set this value will be 1,
 * We should not release library when it is 1. 
 */
DSS_Lib_Status_e http_netctl_lib_status = DSS_LIB_STAT_INVALID_E;
uint8 http_datacall_status = DSS_EVT_INVALID_E;

/* Uart Dbg */
qapi_UART_Handle_t http_dbg_uart_handler;
static char quec_dbg_buffer[128];

#ifdef QUECTEL_HTTPS_SUPPORT

/* *.pem format */
#define HTTPS_CA_PEM			"/datatx/fota_cacert.pem"
#define HTTPS_CERT_PEM			"/datatx/fota_client_cert.pem"
#define HTTPS_PREKEY_PEM		"/datatx/fota_client_key.pem"

/* *.bin format */
#define HTTPS_CA_BIN			"fota_cacert.bin"
#define HTTPS_CERT_BIN			"fota_clientcert.bin"
#define HTTPS_PREKEY_BIN		"fota_clientkey.bin"

uint32_t ssl_ctx_id = 0;		/* http or https identification */
qapi_Net_SSL_Obj_Hdl_t ssl_obj_hdl = 0;

#endif	/* QUECTEL_FOTA_HTTPS_SUPPORT */

#define BYTE_POOL_SIZE       (30720)

ULONG   free_memory_http[BYTE_POOL_SIZE];
TX_BYTE_POOL  byte_pool_httpm;

/*===========================================================================
                               FUNCTION
===========================================================================*/
void http_uart_dbg_init(void)
{
	qapi_Status_t status;
	qapi_UART_Open_Config_t uart_cfg;

	uart_cfg.baud_Rate			= 115200;
	uart_cfg.enable_Flow_Ctrl	= QAPI_FCTL_OFF_E;
	uart_cfg.bits_Per_Char		= QAPI_UART_8_BITS_PER_CHAR_E;
	uart_cfg.enable_Loopback	= 0;
	uart_cfg.num_Stop_Bits		= QAPI_UART_1_0_STOP_BITS_E;
	uart_cfg.parity_Mode		= QAPI_UART_NO_PARITY_E;
	uart_cfg.rx_CB_ISR			= NULL;
	uart_cfg.tx_CB_ISR			= NULL;

	status = qapi_UART_Open(&http_dbg_uart_handler, QAPI_UART_PORT_002_E, &uart_cfg);
	if (QAPI_OK != status)
	{
		return;
	}
	status = qapi_UART_Power_On(http_dbg_uart_handler);
}

void uart_debug_print(const char* fmt, ...) 
{
	va_list arg_list;

	va_start(arg_list, fmt);
    vsnprintf((char *)(quec_dbg_buffer), sizeof(quec_dbg_buffer), (char *)fmt, arg_list);
    va_end(arg_list);
		
	qapi_UART_Transmit(http_dbg_uart_handler, quec_dbg_buffer, strlen(quec_dbg_buffer), NULL);
    qapi_UART_Transmit(http_dbg_uart_handler, "\r\n", strlen("\r\n"), NULL);

	qapi_Timer_Sleep(50, QAPI_TIMER_UNIT_MSEC, true);
}

/*
@func
	dss_net_event_cb
@brief
	Initializes the DSS netctrl library for the specified operating mode.
*/
static void http_net_event_cb
( 
	qapi_DSS_Hndl_t 		hndl,
	void 				   *user_data,
	qapi_DSS_Net_Evt_t 		evt,
	qapi_DSS_Evt_Payload_t *payload_ptr 
)
{
	qapi_Status_t status = QAPI_OK;
	
	uart_debug_print("Data test event callback, event: %d\n", evt);

	switch (evt)
	{
		case QAPI_DSS_EVT_NET_IS_CONN_E:
		{
			uart_debug_print("Data Call Connected.\n");
			http_show_sysinfo();
			/* Signal main task */
  			tx_event_flags_set(&http_signal_handle, DSS_SIG_EVT_CONN_E, TX_OR);
			http_datacall_status = DSS_EVT_NET_IS_CONN_E;
			
			break;
		}
		case QAPI_DSS_EVT_NET_NO_NET_E:
		{
			uart_debug_print("Data Call Disconnected.\n");
			
			if (DSS_EVT_NET_IS_CONN_E == http_datacall_status)
			{
				/* Release Data service handle and netctrl library */
				if (http_dss_handle)
				{
					status = qapi_DSS_Rel_Data_Srvc_Hndl(http_dss_handle);
					if (QAPI_OK == status)
					{
						uart_debug_print("Release data service handle success\n");
						tx_event_flags_set(&http_signal_handle, DSS_SIG_EVT_EXIT_E, TX_OR);
					}
				}
				
				if (DSS_LIB_STAT_SUCCESS_E == http_netctl_lib_status)
				{
					qapi_DSS_Release(QAPI_DSS_MODE_GENERAL);
				}
			}
			else
			{
				/* DSS status maybe QAPI_DSS_EVT_NET_NO_NET_E before data call establishment */
				tx_event_flags_set(&http_signal_handle, DSS_SIG_EVT_NO_CONN_E, TX_OR);
			}

			break;
		}
		default:
		{
			uart_debug_print("Data Call status is invalid.\n");
			
			/* Signal main task */
  			tx_event_flags_set(&http_signal_handle, DSS_SIG_EVT_INV_E, TX_OR);
			http_datacall_status = DSS_EVT_INVALID_E;
			break;
		}
	}
}

void http_show_sysinfo(void)
{
	int i   = 0;
	int j 	= 0;
	unsigned int len = 0;
	uint8 buff[DSS_ADDR_SIZE] = {0}; 
	qapi_Status_t status;
	qapi_DSS_Addr_Info_t info_ptr[DSS_ADDR_INFO_SIZE];

	status = qapi_DSS_Get_IP_Addr_Count(http_dss_handle, &len);
	if (QAPI_ERROR == status)
	{
		uart_debug_print("Get IP address count error\n");
		return;
	}
		
	status = qapi_DSS_Get_IP_Addr(http_dss_handle, info_ptr, len);
	if (QAPI_ERROR == status)
	{
		uart_debug_print("Get IP address error\n");
		return;
	}
	
	j = GET_ADDR_INFO_MIN(len, DSS_ADDR_INFO_SIZE);
	
	for (i = 0; i < j; i++)
	{
		uart_debug_print("<--- static IP address information --->\n");
		http_inet_ntoa(info_ptr[i].iface_addr_s, buff, DSS_ADDR_SIZE);
		uart_debug_print("static IP: %s\n", buff);

		memset(buff, 0, sizeof(buff));
		http_inet_ntoa(info_ptr[i].gtwy_addr_s, buff, DSS_ADDR_SIZE);
		uart_debug_print("Gateway IP: %s\n", buff);

		memset(buff, 0, sizeof(buff));
		http_inet_ntoa(info_ptr[i].dnsp_addr_s, buff, DSS_ADDR_SIZE);
		uart_debug_print("Primary DNS IP: %s\n", buff);

		memset(buff, 0, sizeof(buff));
		http_inet_ntoa(info_ptr[i].dnss_addr_s, buff, DSS_ADDR_SIZE);
		uart_debug_print("Second DNS IP: %s\n", buff);
	}

	uart_debug_print("<--- End of system info --->\n");
}

/*
@func
	http_set_data_param
@brief
	Set the Parameter for Data Call, such as APN and network tech.
*/
static int http_set_data_param(void)
{
    qapi_DSS_Call_Param_Value_t param_info;
	
	/* Initial Data Call Parameter */
	memset(apn, 0, sizeof(apn));
	memset(apn_username, 0, sizeof(apn_username));
	memset(apn_passwd, 0, sizeof(apn_passwd));
	strlcpy(apn, QL_DEF_APN, QAPI_DSS_CALL_INFO_APN_MAX_LEN);

    if (NULL != http_dss_handle)
    {
        /* set data call param */
        param_info.buf_val = NULL;
        param_info.num_val = QAPI_DSS_RADIO_TECH_UNKNOWN;	//Automatic mode(or DSS_RADIO_TECH_LTE)
        uart_debug_print("Setting tech to Automatic\n");
        qapi_DSS_Set_Data_Call_Param(http_dss_handle, QAPI_DSS_CALL_INFO_TECH_PREF_E, &param_info);

		/* set apn */
        param_info.buf_val = apn;
        param_info.num_val = strlen(apn);
        uart_debug_print("Setting APN - %s\n", apn);
        qapi_DSS_Set_Data_Call_Param(http_dss_handle, QAPI_DSS_CALL_INFO_APN_NAME_E, &param_info);
#ifdef QUEC_CUSTOM_APN
		/* set apn username */
		param_info.buf_val = apn_username;
        param_info.num_val = strlen(apn_username);
        uart_debug_print("Setting APN USER - %s\n", apn_username);
        qapi_DSS_Set_Data_Call_Param(http_dss_handle, QAPI_DSS_CALL_INFO_USERNAME_E, &param_info);

		/* set apn password */
		param_info.buf_val = apn_passwd;
        param_info.num_val = strlen(apn_passwd);
        uart_debug_print("Setting APN PASSWORD - %s\n", apn_passwd);
        qapi_DSS_Set_Data_Call_Param(http_dss_handle, QAPI_DSS_CALL_INFO_PASSWORD_E, &param_info);
#endif
		/* set IP version(IPv4 or IPv6) */
        param_info.buf_val = NULL;
        param_info.num_val = QAPI_DSS_IP_VERSION_4;
        uart_debug_print("Setting family to IPv%d\n", param_info.num_val);
        qapi_DSS_Set_Data_Call_Param(http_dss_handle, QAPI_DSS_CALL_INFO_IP_VERSION_E, &param_info);
    }
    else
    {
        uart_debug_print("Dss handler is NULL!!!\n");
		return -1;
    }
	
    return 0;
}

/*
@func
	http_inet_ntoa
@brief
	utility interface to translate ip from "int" to x.x.x.x format.
*/
int32 http_inet_ntoa
(
	const qapi_DSS_Addr_t    inaddr, /* IPv4 address to be converted         */
	uint8                   *buf,    /* Buffer to hold the converted address */
	int32                    buflen  /* Length of buffer                     */
)
{
	uint8 *paddr  = (uint8 *)&inaddr.addr.v4;
	int32  rc = 0;

	if ((NULL == buf) || (0 >= buflen))
	{
		rc = -1;
	}
	else
	{
		if (-1 == snprintf((char*)buf, (unsigned int)buflen, "%d.%d.%d.%d",
							paddr[0],
							paddr[1],
							paddr[2],
							paddr[3]))
		{
			rc = -1;
		}
	}

	return rc;
} /* http_inet_ntoa() */

/*
@func
	http_netctrl_init
@brief
	Initializes the DSS netctrl library for the specified operating mode.
*/
static int http_netctrl_init(void)
{
	int ret_val = 0;
	qapi_Status_t status = QAPI_OK;

	uart_debug_print("Initializes the DSS netctrl library\n");

	/* Initializes the DSS netctrl library */
	if (QAPI_OK == qapi_DSS_Init(QAPI_DSS_MODE_GENERAL))
	{
		http_netctl_lib_status = DSS_LIB_STAT_SUCCESS_E;
		uart_debug_print("qapi_DSS_Init success\n");
	}
	else
	{
		/* @Note: netctrl library has been initialized */
		http_netctl_lib_status = DSS_LIB_STAT_FAIL_E;
		uart_debug_print("DSS netctrl library has been initialized.\n");
	}
	
	/* Registering callback http_dss_handleR */
	do
	{
		uart_debug_print("Registering Callback http_dss_handle\n");
		
		/* Obtain data service handle */
		status = qapi_DSS_Get_Data_Srvc_Hndl(http_net_event_cb, NULL, &http_dss_handle);
		uart_debug_print("http_dss_handle %d, status %d\n", http_dss_handle, status);
		
		if (NULL != http_dss_handle)
		{
			uart_debug_print("Registed http_dss_handler success\n");
			break;
		}

		/* Obtain data service handle failure, try again after 10ms */
		qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_MSEC, true);
	} while(1);

	return ret_val;
}

/*
@func
	http_netctrl_start
@brief
	Start the DSS netctrl library, and startup data call.
*/
int http_netctrl_start(void)
{
	int rc = 0;
	qapi_Status_t status = QAPI_OK;
		
	rc = http_netctrl_init();
	if (0 == rc)
	{
		/* Get valid DSS handler and set the data call parameter */
		http_set_data_param();
	}
	else
	{
		uart_debug_print("quectel_dss_init fail.\n");
		return -1;
	}

	uart_debug_print("qapi_DSS_Start_Data_Call start!!!.\n");
	status = qapi_DSS_Start_Data_Call(http_dss_handle);
	if (QAPI_OK == status)
	{
		uart_debug_print("Start Data service success.\n");
		return 0;
	}
	else
	{
        uart_debug_print("Start Data service failed.\n");
		return -1;
	}
}

/*
@func
	http_netctrl_release
@brief
	Cleans up the DSS netctrl library and close data service.
*/
int http_netctrl_stop(void)
{
	qapi_Status_t stat = QAPI_OK;
	
	if (http_dss_handle)
	{
		stat = qapi_DSS_Stop_Data_Call(http_dss_handle);
		if (QAPI_OK == stat)
		{
			uart_debug_print("Stop data call success\n");
		}
	}
	
	return 0;
}	


boolean write_update_file(int32 handle, char* src, uint32 size)
{
    uint32 len;
    boolean ret_val = FALSE;
	ret_val = qapi_FS_Write(handle, src, size, &len);
	if(size == len && ret_val == QAPI_OK)
	{
        return TRUE;
	}
	else
	{
        return FALSE;
    }
}

void http_client_cb(void* arg, int32 state, void* http_resp)
{
    boolean ret_val = FALSE;
    static boolean file_opened = FALSE;
    qapi_Net_HTTPc_Response_t * resp = NULL;
    static int file_handle;
    resp = (qapi_Net_HTTPc_Response_t *)http_resp;
    uart_debug_print("http_client_cb:%x,%ld,len:%lu,code:%lu,%x",arg,state,resp->length,resp->resp_Code,resp->data);
    if( resp->resp_Code >= 200 && resp->resp_Code < 300)
    {
        if(resp->data != NULL)
        {
            if(file_opened == FALSE)
            {
      
                ret_val = qapi_FS_Open(FILE_PATH, QAPI_FS_O_WRONLY_E | QAPI_FS_O_CREAT_E | QAPI_FS_O_TRUNC_E, &file_handle);
               
                if(ret_val == 0)
                {
                    uart_debug_print("open %s success",FILE_PATH);
                    file_opened = TRUE;
                }  
                else
                {
                    uart_debug_print("open failed:%d",ret_val);
                }
            }
            if (file_opened == TRUE)
            {
                ret_val = write_update_file(file_handle, (char*)resp->data, resp->length);
                if(ret_val != TRUE)
                {
                    uart_debug_print("write_update_file failed");
                }
            }
            if(state == 0 && ret_val == TRUE)
            {
                file_opened = FALSE;
                ret_val = TRUE;
                uart_debug_print("download success");
                qapi_FS_Close(file_handle);
                qapi_Net_HTTPc_Disconnect(http_hadle);
                qapi_Net_HTTPc_Free_sess(http_hadle);
                qapi_Net_HTTPc_Stop();
                tx_event_flags_delete(&http_signal_handle);
            } 
        }
        else
        {
            ret_val = TRUE;
        }
    }
    else
    {

        ret_val = FALSE;
        uart_debug_print("download failed");
    }
    if(ret_val != TRUE)
    {
        file_opened = FALSE;
        qapi_FS_Close(file_handle);
        uart_debug_print("download failed");
        qapi_Net_HTTPc_Disconnect(http_hadle);
        qapi_Net_HTTPc_Free_sess(http_hadle);
        tx_event_flags_delete(&http_signal_handle);
    }
}
/*
@func
	quec_dataservice_entry
@brief
	The entry of data service task.
*/

int quectel_atoi(const char *str)
{
    int value = 0;
    int flag = 1; 

    while (*str == ' ')  
    {
        str++;
    }

    if (*str == '-') 
    {
        flag = 0;
        str++;
    }
    else if (*str == '+')
    {
        flag = 1;
        str++;
    }
    else if (*str >= '9' || *str <= '0') 
    {
        return 0;    
    }

    while (*str != '\0' && *str <= '9' && *str >= '0')
    {
        value = value * 10 + *str - '0';
        str++;
    }

    if (flag == 0) 
    {
        value = -value;
    }

    return value;
}
int32 http_strlcpy
(
char *dst, 
const char *src,
int32  siz
)
{
	char  *d = dst;
	const char *s = src;
	int32 n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0) 
   {
		while (--n != 0) 
		{
			if ((*d++ = *s++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) 
	{
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
		{
			;
		}
	}

	return(s - src - 1);	/* count does not include NUL */
}


int get_url(uint8 * buf)
 {
    int file_handle;
    qapi_FS_Status_t ret_val = -1;
    struct qapi_FS_Stat_Type_s sbuf;
    qapi_FS_Offset_t real_read;
    ret_val = qapi_FS_Stat(URL_PATH, &sbuf);
    if (ret_val != 0)
    {
        return -1;
    }
    ret_val = qapi_FS_Open(URL_PATH, QAPI_FS_O_RDONLY_E , &file_handle);         
    if(ret_val!= 0)
    {
        uart_debug_print("open %s failed",URL_PATH);
        return -1;
    }
    ret_val = qapi_FS_Read(file_handle, (uint8*)buf, sbuf.st_size, &real_read );

    if(ret_val != 0 || real_read != sbuf.st_size)
    {
        uart_debug_print("read %s failed",URL_PATH);
        return -1;
    }
    qapi_FS_Close(file_handle);
    return 0;
}

boolean   http_decode_url
(
uint8            *url, 
uint32           *url_length, 
char             *host,
uint16           *port,
uint8            *file_name
)
{
    uint8      hstr[9];
    uint32    i;
    uint8    *phostnamehead;
    uint8    *phostnameTail;
    boolean      ret = FALSE;
    uint8     url_type;
    uint8   *puri= url;
    uint32   datalen = *url_length;
    *port = HTTP_DEFAULT_PORT;
    do
    {
        memset(hstr,0,9);

        if((*url_length) < 8)
        {
            break;
        }

        memcpy(hstr,url,8);

        for(i=0;i<8;i++)
        {
            hstr[i] = lower((int32)hstr[i]);
        }
        if(strncmp((char *)hstr,(char*)"https://",8) == 0)
        {
            puri = url + 8;
            datalen -= 8;
            url_type = 1;
#ifdef QUECTEL_HTTPS_SUPPORT
			ssl_ctx_id = 1;
#endif
        }
        else if(strncmp((char *)hstr,(char*)"http://",7) == 0)
        {
            puri = url+7;
            datalen -= 7;
            url_type = 0;
#ifdef QUECTEL_HTTPS_SUPPORT
			ssl_ctx_id = 0;
#endif

        }
        else
        {  
            break;
        }
       
        if(url_type == 1)
        {
            *port = HTTPS_DEFAULT_PORT;
        }
        else
        {
             *port = HTTP_DEFAULT_PORT;  
        }
        i=0;

	 if(puri[i] != '[') //chris: normal url  http://220.180.239.201:80/index.html  or http://www.baidu.com
	 {
	 	 	/* parse host name */
        	phostnamehead = puri;
        	phostnameTail = puri;
		
        	while(i<datalen && puri[i] != '/' && puri[i] != ':')
        	{
            		i++;
            		phostnameTail++;
        	}
	 }
	 else //ipv6 url:http://[FEDC:BA98:7654:3210:FEDC:BA98:7654:3210]:80/index.html  or http://[1080:0:0:0:8:800:200C:417A]/index.html
	 {
		datalen -= 1;
		puri += 1;
		
	 	phostnamehead = puri;
		phostnameTail = puri;
	 	while(i < datalen && puri[i] != ']')
	 	{
	 		i++;
			phostnameTail++;
	 	}
		i++;
	 }
        hstr[0] = *phostnameTail;
        *phostnameTail = '\0';
        if(strlen((char*)phostnamehead)  == 0 || strlen((char*)phostnamehead) >= HTTP_DOMAIN_NAME_LENGTH)
        {
            //QL_LOG_MSG_DEBUG("%s", __FUNCTION__);
             break;
        }
        http_strlcpy(host,  (char*)phostnamehead, (strlen((char*)phostnamehead)+1));
        
        *phostnameTail = hstr[0];

        /* IP address URL without port */
        if(datalen >= i)
            datalen -= i;
        else
            datalen = 0;
        if(datalen == 0)
        {
            url[0] = '/';
            *url_length = 1;
            ret = TRUE;
            break;
        }

		/* get port */
		puri+=i;
		i = 0;
		
        if(*puri==':')
        {
            datalen -= 1;
            puri++;
            phostnamehead = puri;
            phostnameTail = puri;

            while(*puri !='/' && i<datalen ){
                puri++;
                i++;
            }		
            
            phostnameTail = puri;
            hstr[0] = *phostnameTail;
            *phostnameTail = '\0';

            *port = quectel_atoi((char *)phostnamehead);
            *phostnameTail = hstr[0];
        }

        if(datalen >= i)
            datalen -= i;
        else
            datalen = 0;
        if(datalen == 0)
        {
             url[0] = '/';
            *url_length = 1;
            ret = TRUE;
            break;
        }

		/* get resouce URI */
        if(*puri=='/')
        {
            i=0;
            while(i<datalen)
            {
                url[i]=puri[i];
                i++;
            }		
            *url_length= datalen;
            *(url+datalen)='\0';
            http_strlcpy((char*)file_name, (char*)url, strlen((char*)url)+1);
        }
        else
        {
            url[0] = '/';
            *url_length= 1;
        }
        ret = TRUE;
        
    }while(FALSE);
    if(ret == FALSE)
    {
    	 url[0]= '\0';
		*url_length = 0;
		memset((void *)host, 0, HTTP_DOMAIN_NAME_LENGTH);
    }
		
    return ret;

}

#ifdef QUECTEL_HTTPS_SUPPORT
int http_store_read_from_EFS_file(const char *name, void **buffer_ptr, size_t *buffer_size)
{
	int bytes_read;
	int efs_fd = -1;
	struct qapi_FS_Stat_Type_s stat;
	uint8 *file_buf = NULL;
	stat.st_size = 0;

	if ((!name) || (!buffer_ptr) ||(!buffer_size))
	{
		uart_debug_print("Reading SSL from EFS file failed!\n");
		return QAPI_ERROR;
	}

	if (qapi_FS_Open(name, QAPI_FS_O_RDONLY_E, &efs_fd) < 0)
	{
		uart_debug_print("Opening EFS EFS file %s failed\n", name);
		return QAPI_ERROR;
	}

	if (qapi_FS_Stat_With_Handle(efs_fd, &stat) < 0) 
	{
		uart_debug_print("Reading EFS file %s failed\n", name);
		return QAPI_ERROR;
	}

	uart_debug_print("Reading EFS file size %d \n", stat.st_size);
	
	tx_byte_allocate(&byte_pool_httpm, (VOID **) &file_buf, stat.st_size, TX_NO_WAIT);
	if (file_buf  == NULL) 
	{
		uart_debug_print("SSL_cert_store: QAPI_ERR_NO_MEMORY \n");
		return QAPI_ERR_NO_MEMORY;
	}

	qapi_FS_Read(efs_fd, file_buf, stat.st_size, &bytes_read);
	if ((bytes_read < 0) || (bytes_read != stat.st_size)) 
	{
		tx_byte_release(file_buf);
		uart_debug_print("SSL_cert_store: Reading EFS file error\n");
		return QAPI_ERROR;
	}

	*buffer_ptr = file_buf;
	*buffer_size = stat.st_size;

	qapi_FS_Close(efs_fd);

	return QAPI_OK;
}


static qapi_Status_t http_ssl_conn_obj_config(SSL_INST *ssl)
{
	qapi_Status_t ret_val = QAPI_OK;
	
	/* default eight encryption suites */
	ssl->config.cipher[0] = QAPI_NET_TLS_RSA_WITH_AES_128_CBC_SHA;
	ssl->config.cipher[1] = QAPI_NET_TLS_RSA_WITH_AES_256_CBC_SHA;
	ssl->config.cipher[2] = QAPI_NET_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA;
	ssl->config.cipher[3] = QAPI_NET_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA;
	ssl->config.cipher[4] = QAPI_NET_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA;
	ssl->config.cipher[5] = QAPI_NET_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA;
	ssl->config.cipher[6] = QAPI_NET_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA;
	ssl->config.cipher[7] = QAPI_NET_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384;
	
	ssl->config.max_Frag_Len = 4096;
	ssl->config.max_Frag_Len_Neg_Disable = 0;
	ssl->config.protocol = QAPI_NET_SSL_PROTOCOL_TLS_1_2;
	ssl->config.verify.domain = 0;
	ssl->config.verify.match_Name[0] = '\0';
	ssl->config.verify.send_Alert = 0;
	ssl->config.verify.time_Validity = 0;	/* Don't check certification expiration */

	return ret_val;
}

static int http_ssl_verify_method(ssl_verify_method_e *verify_method)
{
	int ca_fd = -1;
	int cert_fd = -1;
	int key_fd = -1;
	qapi_FS_Status_t fs_stat = QAPI_OK;

	*verify_method = QHTTPS_SSL_NO_METHOD;

	/* check CAList is exist or not */
	fs_stat = qapi_FS_Open(HTTPS_CA_PEM, QAPI_FS_O_RDONLY_E, &ca_fd);
	if ((fs_stat != QAPI_OK) || (ca_fd < 0))
	{
		uart_debug_print("Cannot find or open CAList file in EFS");
		*verify_method = QHTTPS_SSL_NO_METHOD;
	}
	else
	{
		*verify_method = QHTTPS_SSL_ONEWAY_METHOD;
		
		/* check client certificate is exist or not */
		fs_stat = qapi_FS_Open(HTTPS_CERT_PEM, QAPI_FS_O_RDONLY_E, &cert_fd);
		if ((fs_stat != QAPI_OK) || (cert_fd < 0))
		{
			uart_debug_print("Cannot find or open Cert file in EFS");
			*verify_method = QHTTPS_SSL_ONEWAY_METHOD;
		}
		else
		{
			*verify_method = QHTTPS_SSL_TWOWAY_METHOD;
			
			/* if client certificate is exist, client private key must be existed */
			fs_stat = qapi_FS_Open(HTTPS_PREKEY_PEM, QAPI_FS_O_RDONLY_E, &key_fd);
			if ((fs_stat != QAPI_OK) || (key_fd < 0))
			{
				uart_debug_print("Cannot find or open key file in EFS");
				return -1;	//miss client key 
			}
			
			qapi_FS_Close(cert_fd);
		}

		qapi_FS_Close(ca_fd);
	}

	return 0;
}

static qapi_Status_t http_ssl_cert_load(SSL_INST *ssl)
{
	qapi_Status_t result = QAPI_OK;

	int32_t ret_val = 0;

#if 0	
	int cert_data_buf_len;
	char *cert_data_buf;
#endif

    uint8_t *cert_Buf = NULL; 
    uint32_t cert_Size = 0;
	uint8_t *key_Buf = NULL;
	uint32_t key_Size = 0;

//	int32 cert_size = 0;
	qapi_Net_SSL_Cert_Info_t cert_info;
	qapi_NET_SSL_CA_Info_t calist_info[QAPI_NET_SSL_MAX_CA_LIST];

	ssl_verify_method_e verify_method;

	if (ssl_ctx_id)
	{
		uart_debug_print("Start https process");

		if (0 != http_ssl_verify_method(&verify_method))
		{
			uart_debug_print("Miss certificates in EFS, error return");
			return QAPI_ERROR;
		}
		
		switch (verify_method)
		{
			case QHTTPS_SSL_TWOWAY_METHOD:
			{
				/* Read the client certificate information */
			    ret_val = http_store_read_from_EFS_file((char *)HTTPS_CERT_PEM, (void **)&cert_Buf, (size_t *)&cert_Size);
				uart_debug_print("Read %s, result %d", HTTPS_CERT_PEM, ret_val);
			    if (QAPI_OK != ret_val) 
			    {
			         uart_debug_print("ERROR: Reading client certificate from EFS failed!! \r\n");
			         result = QAPI_ERROR;
			    }

			    /* Read the client key information */
			    ret_val = http_store_read_from_EFS_file((char *)HTTPS_PREKEY_PEM, (void **)&key_Buf, (size_t *)&key_Size);
				uart_debug_print("Read %s, result %d", HTTPS_PREKEY_PEM, ret_val);
			    if (QAPI_OK != ret_val) 
			    {
			         uart_debug_print("ERROR: Reading key information from EFS failed!! \r\n");
			         result = QAPI_ERROR;
			    }

				/* Update the client certificate information */
				cert_info.cert_Type = QAPI_NET_SSL_CERTIFICATE_E; 
			    cert_info.info.cert.cert_Buf = cert_Buf;
			    cert_info.info.cert.cert_Size = cert_Size;
			    cert_info.info.cert.key_Buf = key_Buf;
			    cert_info.info.cert.key_Size = key_Size;
			    //cert_info.info.cert.pass_Key = https_fota_pass;

				/* Convert and store the certificate */ 
				result = qapi_Net_SSL_Cert_Convert_And_Store(&cert_info, HTTPS_CERT_BIN);
				uart_debug_print("%s qapi_Net_SSL_Cert_Convert_And_Store: %d", HTTPS_CERT_BIN, result);
				
				if (result == QAPI_OK)
				{
					if (qapi_Net_SSL_Cert_Load(ssl->sslCtx, QAPI_NET_SSL_CERTIFICATE_E, HTTPS_CERT_BIN) < 0)
					{
						uart_debug_print("ERROR: Unable to load client cert from FLASH");
						//return QCLI_STATUS_ERROR_E;
					}
				}

				/* continue to load CAList */
			}
			case QHTTPS_SSL_ONEWAY_METHOD:
			{
				/* Store CA List */
				ret_val = http_store_read_from_EFS_file(HTTPS_CA_PEM, (void **)&calist_info[0].ca_Buf, (size_t *)&calist_info[0].ca_Size);
				uart_debug_print("Read %s, result %d", HTTPS_CA_PEM, ret_val);

			    if (QAPI_OK != ret_val) 
			    {
			         uart_debug_print("ERROR: Reading ca information from EFS failed!! \r\n");
			         result = QAPI_ERROR;
			    }

				cert_info.info.ca_List.ca_Info[0] = &calist_info[0];
			    cert_info.info.ca_List.ca_Cnt = 1;
				cert_info.cert_Type = QAPI_NET_SSL_CA_LIST_E;
				
				result = qapi_Net_SSL_Cert_Convert_And_Store(&cert_info, HTTPS_CA_BIN);
				//result = qapi_Net_SSL_Cert_Store(HTTPS_CA_BIN, QAPI_NET_SSL_CA_LIST_E, cert_data_buf, cert_data_buf_len);
				uart_debug_print("%s qapi_Net_SSL_Cert_Convert_And_Store: %d", HTTPS_CA_BIN, result);
				
				if (result == QAPI_OK)
				{
					if (qapi_Net_SSL_Cert_Load(ssl->sslCtx, QAPI_NET_SSL_CA_LIST_E, HTTPS_CA_BIN) < 0)
					{
						uart_debug_print("ERROR: Unable to load CA from FLASH");
						//return QCLI_STATUS_ERROR_E;
					}
				}

				break;
			}			
			default:
			{
				uart_debug_print("Don't need to verify certifications");
				break;
			}
		}
	}
	
#if 0	/* not use */	
	/* Store PSK */
	cert_info.cert_Type = QAPI_NET_SSL_PSK_TABLE_E;
	result = qapi_Net_SSL_Cert_Convert_And_Store(&cert_info, HTTPS_PREKEY_BIN);
	uart_debug_print("%s convert and store failed: %d", HTTPS_PREKEY_BIN, result);
	//result = qapi_Net_SSL_Cert_Store(HTTPS_FOTA_CLIENT_KEY, QAPI_NET_SSL_PSK_TABLE_E, cert_data_buf, cert_data_buf_len);
	if (result == QAPI_OK)
	{
		if (qapi_Net_SSL_Cert_Load(ssl->sslCtx, QAPI_NET_SSL_PSK_TABLE_E, HTTPS_PREKEY_BIN) < 0)
		{
			uart_debug_print("ERROR: Unable to load PSK from FLASH");
			//return QCLI_STATUS_ERROR_E;
		}
	}
#endif
	return result;
}

int http_ssl_config(SSL_INST *ssl)
{
	int ret_val = 0;	
	qapi_Status_t result = QAPI_OK;
	qapi_Net_SSL_Role_t role = QAPI_NET_SSL_CLIENT_E;	/* TLS Client object creation. */

	memset(ssl, 0, sizeof(SSL_INST));	
	ssl->role = role;
	ssl->sslCtx = qapi_Net_SSL_Obj_New(role);
	if (ssl->sslCtx == QAPI_NET_SSL_INVALID_HANDLE)
	{
		uart_debug_print("ERROR: Unable to create SSL context");
		return -1;
	}

	/* TLS Configuration of a Connection Object */
	result = http_ssl_conn_obj_config(ssl);
	
	/* 
	 * allocate memory and read the certificate from certificate server or EFS.
	 * Once cert_data_buf filled with valid SSL certificate, Call QAPI to Store and Load 
	 */
	result = http_ssl_cert_load(ssl);
	if (result != QAPI_OK)
	{
		uart_debug_print("http_ssl_cert_load return error");
		ret_val = -1;
	}
	
	return ret_val;
}
#endif	/* QUECTEL_HTTPS_SUPPORT */

int quectel_task_entry(void)
{
    int ret = -1;
    uint32 dss_event = 0;
    int result = TRUE;
    uint8 file_name[HTTP_MAX_PATH_LENGTH+1] = {0};
    char host[HTTP_DOMAIN_NAME_LENGTH+1] = {0};
    uint8 buf[300] = {0};
    uint16 port;
    uint32 len = 0;
#ifdef QUECTEL_HTTPS_SUPPORT
	SSL_INST http_ssl;
#endif
    
    qapi_Timer_Sleep(10, QAPI_TIMER_UNIT_SEC, true);
    http_uart_dbg_init();
    ret = get_url(buf);
    if(ret != 0)
    {
        uart_debug_print("read config file fialed");
        return FALSE;
    }
    len = strlen((const char *)buf);
    http_decode_url((uint8*)buf, &len, host, &port, file_name);
    uart_debug_print("host:%s,port:%d,source:%s", host, port, file_name);
    tx_event_flags_create(&http_signal_handle, "dss_signal_event");
	tx_event_flags_set(&http_signal_handle, 0x0, TX_AND);

	/* create a memory pool */
	tx_byte_pool_create(&byte_pool_httpm, "byte pool http", free_memory_http, BYTE_POOL_SIZE);
	
    ret = http_netctrl_start();
	if (ret != 0)
	{
        return FALSE;
	}
	while(1)
    {
       tx_event_flags_get(&http_signal_handle, DSS_SIG_EVT_CONN_E|DSS_SIG_EVT_DIS_E|DSS_SIG_EVT_EXIT_E|DSS_SIG_EVT_NO_CONN_E, TX_OR, &dss_event, TX_WAIT_FOREVER);
       if(dss_event&DSS_SIG_EVT_CONN_E)
       {
            uart_debug_print("dss_event:%x",dss_event);
            tx_event_flags_set(&http_signal_handle, ~DSS_SIG_EVT_CONN_E, TX_AND);
            if(qapi_Net_DNSc_Is_Started() == 0)
            {
                qapi_Net_DNSc_Command(QAPI_NET_DNS_START_E);
                qapi_Net_DNSc_Add_Server("223.5.5.5", 0);
                qapi_Net_DNSc_Add_Server("114.114.114.114", 1);

            }
            qapi_Net_HTTPc_Start();

#ifdef QUECTEL_HTTPS_SUPPORT
			/* configure https context */
			if (ssl_ctx_id)
			{
				/* config object and certificate */
				if (0 != http_ssl_config(&http_ssl))
				{
					uart_debug_print("ERROR: Config ssl object and certificates error");
					result = FALSE;
					break;
				}
				
				/* create a SSL session */
				ssl_obj_hdl = http_ssl.sslCtx;
				http_ssl.sslCon = qapi_Net_SSL_Con_New(http_ssl.sslCtx, QAPI_NET_SSL_TLS_E);
				if (http_ssl.sslCon == QAPI_NET_SSL_INVALID_HANDLE)
				{
					uart_debug_print("ERROR: Unable to create SSL context");
					result = FALSE;
					break;
				}
				
				if (QAPI_OK != qapi_Net_SSL_Configure(http_ssl.sslCon, &http_ssl.config))
				{
					uart_debug_print("ERROR: SSL configure failed");
					result = FALSE;
					break;
				}

				/* https client session */
				http_hadle = qapi_Net_HTTPc_New_sess(6000, http_ssl.sslCtx, http_client_cb, NULL, 1024, 1024);
				ret = qapi_Net_HTTPc_Configure_SSL(http_hadle, &http_ssl.config);
				
				uart_debug_print("Start HTTPS connection, SSL config ret[%d], result:[%d]", ret, result);
			}
            else
            {
                http_hadle = qapi_Net_HTTPc_New_sess(6000, 0, http_client_cb, NULL, 1024, 1024);
            }
#else
			/* http client session */
            http_hadle = qapi_Net_HTTPc_New_sess(6000, 0, http_client_cb, NULL, 1024, 1024);
#endif	/* QUECTEL_HTTPS_SUPPORT */
            if ( http_hadle == NULL)
            {
                uart_debug_print("qapi_Net_HTTPc_New_sess ERROR");
                result = FALSE;
                break;
            }
            ret =qapi_Net_HTTPc_Connect(http_hadle, host, port);
            if(ret != QAPI_OK)
            {
                
                uart_debug_print("qapi_Net_HTTPc_Connect ERROR :%d",ret);
                result = FALSE;
                break;
            }
            ret =qapi_Net_HTTPc_Request(http_hadle, QAPI_NET_HTTP_CLIENT_GET_E, file_name); 
            if(ret != QAPI_OK)
            {
                uart_debug_print("qapi_Net_HTTPc_Request head ERROR :%d",ret);
                result = FALSE;
                break;
            }
            break;
       }
       else if(dss_event&DSS_SIG_EVT_INV_E)
       {
            uart_debug_print("DSS_SIG_EVT_INV_E Signal\n");
			tx_event_flags_set(&http_signal_handle, ~DSS_SIG_EVT_INV_E, TX_AND);
       } 
       else if (dss_event & DSS_SIG_EVT_NO_CONN_E)
	   {
			uart_debug_print("DSS_SIG_EVT_NO_CONN_E Signal\n");
			tx_event_flags_set(&http_signal_handle, ~DSS_SIG_EVT_NO_CONN_E, TX_AND);
	   }
       else if (dss_event & DSS_SIG_EVT_EXIT_E)
	   {
			uart_debug_print("DSS_SIG_EVT_EXIT_E Signal\n");
			tx_event_flags_set(&http_signal_handle, ~DSS_SIG_EVT_EXIT_E, TX_AND);
			tx_event_flags_delete(&http_signal_handle);
			break;
		}
		else
		{
			uart_debug_print("Unkonw Signal\n");
		}

    }
    if(result == FALSE)
    {
        uart_debug_print("HTTP DOWNLOAD ERROR");
        tx_event_flags_delete(&http_signal_handle);
    }
    return result;

}
#endif /*__EXAMPLE_HTTP__*/