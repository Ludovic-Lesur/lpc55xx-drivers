/*
 * usb_hs_device.h
 *
 *  Created on: 15 mar. 2023
 *      Author: Ludo
 */

#ifndef __USB_HS_DEVICE_H__
#define __USB_HS_DEVICE_H__

#include "error.h"
#include "syscon.h"
#include "systick.h"
#include "types.h"
#include "usb_hs_phy.h"

/*** USB_HS_DEVICE structures ***/

/*!******************************************************************
 * \enum USB_HS_DEVICE_status_t
 * \brief USB HS DEVICE driver error codes.
 *******************************************************************/
typedef enum {
    // Driver errors.
    USB_HS_DEVICE_SUCCESS = 0,
    USB_HS_DEVICE_ERROR_NULL_PARAMETER,
    USB_HS_DEVICE_ERROR_ALREADY_INITIALIZED,
    USB_HS_DEVICE_ERROR_UNINITIALIZED,
    USB_HS_DEVICE_ERROR_SPEED,
    USB_HS_DEVICE_ERROR_ADDRESS,
    USB_HS_DEVICE_ERROR_ENDPOINT_ALREADY_REGISTERED,
    USB_HS_DEVICE_ERROR_ENDPOINT_NOT_REGISTERED,
    USB_HS_DEVICE_ERROR_ENDPOINT_NUMBER,
    USB_HS_DEVICE_ERROR_ENDPOINT_PHYSICAL_INDEX,
    USB_HS_DEVICE_ERROR_ENDPOINT_TRANSFER_TYPE,
    USB_HS_DEVICE_ERROR_ENDPOINT_DIRECTION,
    USB_HS_DEVICE_ERROR_ENDPOINT_BUFFER_MODE,
    USB_HS_DEVICE_ERROR_RAM_MALLOC_SIZE,
    USB_HS_DEVICE_ERROR_RAM_MALLOC,
    USB_HS_DEVICE_ERROR_RAM_FREE_ADDRESS,
    USB_HS_DEVICE_ERROR_RAM_FREE_SIZE,
    USB_HS_DEVICE_ERROR_PACKET_SIZE_OVERFLOW,
    // Low level drivers errors.
    USB_HS_DEVICE_ERROR_BASE_USB_HS_PHY = ERROR_BASE_STEP,
    USB_HS_DEVICE_ERROR_BASE_SYSCON = (USB_HS_DEVICE_ERROR_BASE_USB_HS_PHY + USB_HS_PHY_ERROR_BASE_LAST),
    USB_HS_DEVICE_ERROR_BASE_SYSTICK = (USB_HS_DEVICE_ERROR_BASE_SYSCON + SYSCON_ERROR_BASE_LAST),
    // Last base value.
    USB_HS_DEVICE_ERROR_BASE_LAST = (USB_HS_DEVICE_ERROR_BASE_SYSTICK + SYSTICK_ERROR_BASE_LAST)
} USB_HS_DEVICE_status_t;

/*!******************************************************************
 * \enum USB_endpoint_direction_t
 * \brief USB endpoint directions list.
 *******************************************************************/
typedef enum {
    USB_HS_DEVICE_ENDPOINT_DIRECTION_OUT = 0,
    USB_HS_DEVICE_ENDPOINT_DIRECTION_IN,
    USB_HS_DEVICE_ENDPOINT_DIRECTION_LAST
} USB_HS_DEVICE_endpoint_direction_t;

/*!******************************************************************
 * \enum USB_endpoint_transfer_type_t
 * \brief USB endpoint transfer types list.
 *******************************************************************/
typedef enum {
    USB_HS_DEVICE_ENDPOINT_TRANSFER_TYPE_CONTROL = 0,
    USB_HS_DEVICE_ENDPOINT_TRANSFER_TYPE_ISOCHRONOUS,
    USB_HS_DEVICE_ENDPOINT_TRANSFER_TYPE_BULK,
    USB_HS_DEVICE_ENDPOINT_TRANSFER_TYPE_INTERRUPT,
    USB_HS_DEVICE_ENDPOINT_TRANSFER_TYPE_LAST
} USB_HS_DEVICE_endpoint_transfer_type_t;

/*!******************************************************************
 * \enum USB_request_operation_t
 * \brief USB request operations list.
 *******************************************************************/
typedef enum {
    USB_HS_DEVICE_REQUEST_OPERATION_NOT_SUPPORTED = 0,
    USB_HS_DEVICE_REQUEST_OPERATION_READ,
    USB_HS_DEVICE_REQUEST_OPERATION_WRITE,
    USB_HS_DEVICE_REQUEST_OPERATION_WRITE_NO_DATA,
    USB_HS_DEVICE_REQUEST_OPERATION_LAST
} USB_HS_DEVICE_request_operation_t;

/*!******************************************************************
 * \fn USB_HS_DEVICE_endpoint_cb_t
 * \brief USB endpoint transfer completion callback.
 *******************************************************************/
typedef void (*USB_HS_DEVICE_endpoint_cb_t)(void);

/*!******************************************************************
 * \fn USB_HS_DEVICE_setup_cb_t
 * \brief USB setup packet reception callback.
 *******************************************************************/
typedef void (*USB_HS_DEVICE_setup_cb_t)(USB_HS_DEVICE_request_operation_t* request_operation);

/*!******************************************************************
 * \struct USB_physical_endpoint_t
 * \brief USB physical endpoint descriptor structure.
 *******************************************************************/
typedef struct {
    uint8_t number;
    USB_HS_DEVICE_endpoint_direction_t direction;
    USB_HS_DEVICE_endpoint_transfer_type_t transfer_type;
    uint16_t max_packet_size_bytes;
    USB_HS_DEVICE_endpoint_cb_t callback;
} USB_HS_DEVICE_endpoint_t;

/*** USB_HS_DEVICE functions ***/

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_init(uint8_t nvic_priority)
 * \brief Init high speed USB device driver.
 * \param[in]   nvic_priority: Interrupt priority.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_init(uint8_t nvic_priority);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_de_init(void)
 * \brief Release high speed USB device driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_de_init(void);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_reset(void)
 * \brief Reset high speed USB device driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_reset(void);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_register_setup_callback(USB_HS_DEVICE_setup_cb_t setup_callback)
 * \brief Register specific setup callback.
 * \param[in]   setup_callback: Function to call on setup event.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_register_setup_callback(USB_HS_DEVICE_setup_cb_t setup_callback);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_register_endpoint(USB_HS_DEVICE_endpoint_t* endpoint)
 * \brief Register end-point in the high speed USB device driver.
 * \param[in]   endpoint: Pointer to the physical endpoint to register.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_register_endpoint(USB_HS_DEVICE_endpoint_t* endpoint);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_unregister_endpoint(USB_HS_DEVICE_endpoint_t* endpoint)
 * \brief Unregister end-point in the high speed USB device driver.
 * \param[in]   endpoint: Pointer to the physical endpoint to remove.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_unregister_endpoint(USB_HS_DEVICE_endpoint_t* endpoint);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_set_address(uint8_t device_address)
 * \brief Set USB device address.
 * \param[in]   device_address: Address to set.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_set_address(uint8_t device_address);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_start(void)
 * \brief Start high speed USB device driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_start(void);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_stop(void)
 * \brief Stop high speed USB device driver.
 * \param[in]   none
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_stop(void);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_write(USB_HS_DEVICE_endpoint_t* endpoint, uint8_t* data_in, uint32_t data_in_size)
 * \brief Write data to USB bus.
 * \param[in]   endpoint: Pointer to the physical endpoint to use.
 * \param[in]   data_in: Pointer to the data to write.
 * \param[in]   data_in_size: Number of bytes to write.
 * \param[out]  none
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_write(USB_HS_DEVICE_endpoint_t* endpoint, uint8_t* data_in, uint32_t data_in_size);

/*!******************************************************************
 * \fn USB_HS_DEVICE_status_t USB_HS_DEVICE_read(USB_HS_DEVICE_endpoint_t* endpoint, uint8_t* data_out, uint32_t* data_out_size)
 * \brief Read data from USB bus.
 * \param[in]   endpoint: Pointer to the physical endpoint to use.
 * \param[out]  data_out: Pointer to the data to read.
 * \param[out]  data_out_size: Pointer to the number of read bytes.
 * \retval      Function execution status.
 *******************************************************************/
USB_HS_DEVICE_status_t USB_HS_DEVICE_read(USB_HS_DEVICE_endpoint_t* endpoint, uint8_t** data_out, uint32_t* data_out_size);

/*******************************************************************/
#define USB_HS_DEVICE_exit_error(base) { ERROR_check_exit(usb_hs_device_status, USB_HS_DEVICE_SUCCESS, base) }

/*******************************************************************/
#define USB_HS_DEVICE_stack_error(base) { ERROR_check_stack(usb_hs_device_status, USB_HS_DEVICE_SUCCESS, base) }

/*******************************************************************/
#define USB_HS_DEVICE_stack_exit_error(base, code) { ERROR_check_stack_exit(usb_hs_device_status, USB_HS_DEVICE_SUCCESS, base, code) }

#endif /* __USB_HS_DEVICE_H__ */
