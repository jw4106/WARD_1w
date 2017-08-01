#ifndef __ward_1w_H__
#define __ward_1w_H__

#include <app.h>
#include <glib.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#define TAG "HelloAccessoryConsumer"

void     initialize_sap();
gboolean find_peers();
gboolean request_service_connection(void);
gboolean terminate_service_connection(void);
gboolean send_data(char *message);
void     update_ui(char *data);

#define NUM_OF_ITEMS 5

void initialize_sap();
void update_ui(char *data);

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "ward_1w"

#if !defined(PACKAGE)
#define PACKAGE "org.example.ward_1w"
#endif

#endif /* __ward_1w_H__ */
