#include <tizen.h>
#include "ward_1w.h"
#include <watch_app.h>
#include <sensor.h>
#include <glib.h>

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *label;
	Evas_Object *labelg;
	Evas_Object *labelm;
	Evas_Object *labelc;
	Evas_Object *button_start;
	Evas_Object *button_end;
	Evas_Object *grid;
} appdata_s;

struct _sensor_info {
    sensor_h sensor; /* Sensor handle */
    sensor_listener_h sensor_listener; /* Sensor listener */
};

#define TEXT_BUF_SIZE 256
float ax, ay, az;
float gx, gy, gz;
float mx, my, mz;
float cx, cy, cz;
char valuea[5] = "A\n";
char valueg[5] = "G\n";
char valuem[5] = "M\n";
char valuec[5] = "C\n";

typedef struct appdata appdata_s;
typedef struct _sensor_info sensorinfo_s;
static sensorinfo_s sensor_info;
static sensorinfo_s sensor_info_g;
static sensorinfo_s sensor_info_m;
static sensorinfo_s sensor_info_c;

//-------------------------------------------------------------------------------------
//char* get_write_filepath(char *filename)
//{
//    char write_filepath[1000] = {0,};
//    char *resource_path = app_get_data_path(); // get the application data directory path
//    if(resource_path)
//    {
//        snprintf(write_filepath,1000,"%s%s",resource_path,filename);
//        free(resource_path);
//    }
//    return write_filepath;
//}
//
//static char* write_file(const char* filepath, const char* buf)
//{
//    FILE *fp;
//    fp = fopen(filepath,"w");
//    fputs(buf,fp);
//    fclose(fp);
//}

//-------------------------------------------------------------------------------------

static void
_new_sensor_value(sensor_h sensor, sensor_event_s *sensor_data, void *user_data)
{
    char watch_text[TEXT_BUF_SIZE];

    appdata_s *ad = (appdata_s*)user_data;

	sensor_type_e type;
	sensor_get_type(sensor, &type);
    if (type == SENSOR_ACCELEROMETER) {
        ax = sensor_data->values[0];
        ay = sensor_data->values[1];
        az = sensor_data->values[2];

//        char arrayx[10];
//        sprintf(arrayx, "%f", sensor_data->values[0]);
//        strcat(valuea, arrayx);
//        strcat(valuea, "\t");
//        char arrayy[10];
//        sprintf(arrayy, "%f", sensor_data->values[1]);
//        strcat(valuea, arrayy);
//        strcat(valuea, "\t");
//        char arrayz[10];
//        sprintf(arrayz, "%f", sensor_data->values[2]);
//        strcat(valuea, arrayz);
//        strcat(valuea, "\n");
    }
    if (type == SENSOR_GYROSCOPE) {
        gx = sensor_data->values[0];
        gy = sensor_data->values[1];
        gz = sensor_data->values[2];

//        char arrayx[10];
//        sprintf(arrayx, "%f", sensor_data->values[0]);
//        strcat(valueg, arrayx);
//        strcat(valueg, "\t");
//        char arrayy[10];
//        sprintf(arrayy, "%f", sensor_data->values[1]);
//        strcat(valueg, arrayy);
//        strcat(valueg, "\t");
//        char arrayz[10];
//        sprintf(arrayz, "%f", sensor_data->values[2]);
//        strcat(valueg, arrayz);
//        strcat(valueg, "\n");
    }
    if (type == SENSOR_MAGNETIC) {
        mx = sensor_data->values[0];
        my = sensor_data->values[1];
        mz = sensor_data->values[2];

//        char arrayx[10];
//        sprintf(arrayx, "%f", sensor_data->values[0]);
//        strcat(valuem, arrayx);
//        strcat(valuem, "\t");
//        char arrayy[10];
//        sprintf(arrayy, "%f", sensor_data->values[1]);
//        strcat(valuem, arrayy);
//        strcat(valuem, "\t");
//        char arrayz[10];
//        sprintf(arrayz, "%f", sensor_data->values[2]);
//        strcat(valuem, arrayz);
//        strcat(valuem, "\n");
    }
    if (type == SENSOR_ORIENTATION) {
        cx = sensor_data->values[0];
        cy = sensor_data->values[1];
        cz = sensor_data->values[2];

//        char arrayx[10];
//        sprintf(arrayx, "%f", sensor_data->values[0]);
//        strcat(valuec, arrayx);
//        strcat(valuec, "\t");
//        char arrayy[10];
//        sprintf(arrayy, "%f", sensor_data->values[1]);
//        strcat(valuec, arrayy);
//        strcat(valuec, "\t");
//        char arrayz[10];
//        sprintf(arrayz, "%f", sensor_data->values[2]);
//        strcat(valuec, arrayz);
//        strcat(valuec, "\n");
    }
	snprintf(watch_text, TEXT_BUF_SIZE, "<align=center>Accelerometer<br/>%02f<br/>%02f<br/>%02f</align>", ax, ay, az);
    elm_object_text_set(ad->label, watch_text);
}

static void
create_sensor(appdata_s *ad)
{
    sensor_error_e err = SENSOR_ERROR_NONE;
    sensor_error_e err_g = SENSOR_ERROR_NONE;
    sensor_error_e err_m = SENSOR_ERROR_NONE;
    sensor_error_e err_c = SENSOR_ERROR_NONE;

    sensor_get_default_sensor(SENSOR_ACCELEROMETER, &sensor_info.sensor);
    sensor_get_default_sensor(SENSOR_GYROSCOPE, &sensor_info_g.sensor);
    sensor_get_default_sensor(SENSOR_MAGNETIC, &sensor_info_m.sensor);
    sensor_get_default_sensor(SENSOR_ORIENTATION, &sensor_info_c.sensor);

    err = sensor_create_listener(sensor_info.sensor, &sensor_info.sensor_listener);
    err_g = sensor_create_listener(sensor_info_g.sensor, &sensor_info_g.sensor_listener);
    err_m = sensor_create_listener(sensor_info_m.sensor, &sensor_info_m.sensor_listener);
    err_c = sensor_create_listener(sensor_info_c.sensor, &sensor_info_c.sensor_listener);

    sensor_listener_set_event_cb(sensor_info.sensor_listener, 38, _new_sensor_value, ad);
    sensor_listener_set_event_cb(sensor_info_g.sensor_listener, 38, _new_sensor_value, ad);
    sensor_listener_set_event_cb(sensor_info_m.sensor_listener, 38, _new_sensor_value, ad);
    sensor_listener_set_event_cb(sensor_info_c.sensor_listener, 38, _new_sensor_value, ad);

    sensor_listener_set_option(sensor_info.sensor_listener, SENSOR_OPTION_ALWAYS_ON);
    sensor_listener_set_option(sensor_info_g.sensor_listener, SENSOR_OPTION_ALWAYS_ON);
    sensor_listener_set_option(sensor_info_m.sensor_listener, SENSOR_OPTION_ALWAYS_ON);
    sensor_listener_set_option(sensor_info_c.sensor_listener, SENSOR_OPTION_ALWAYS_ON);
}

void
clicked_start(void *data, Evas_Object *obj, void *event_info)
{
    sensor_listener_start(sensor_info.sensor_listener);
    sensor_listener_start(sensor_info_g.sensor_listener);
    sensor_listener_start(sensor_info_m.sensor_listener);
    sensor_listener_start(sensor_info_c.sensor_listener);
}

void
clicked_stop(void *data, Evas_Object *obj, void *event_info)
{
    sensor_listener_stop(sensor_info.sensor_listener);
    sensor_listener_stop(sensor_info_g.sensor_listener);
    sensor_listener_stop(sensor_info_m.sensor_listener);
    sensor_listener_stop(sensor_info_c.sensor_listener);

//    char *filepatha;
//    char *filepathg;
//    char *filepathm;
//    char *filepathc;
//    filepatha=get_write_filepath("a.txt");
//    filepathg=get_write_filepath("g.txt");
//    filepathm=get_write_filepath("m.txt");
//    filepathc=get_write_filepath("c.txt");
//    write_file(filepatha,valuea);
//    write_file(filepathg,valueg);
//    write_file(filepathm,valuem);
//    write_file(filepathc,valuec);

}

static void
create_base_gui(appdata_s *ad)
{

	/* Window */
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}

	//evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	//eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	/* Conformant */
	ad->conform = elm_conformant_add(ad->win);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	/* Grid */
	ad->grid=elm_grid_add(ad->conform);
	elm_object_content_set(ad->conform,ad->grid);
	elm_grid_size_set(ad->grid,300,200);
	evas_object_show(ad->grid);

	/* Label Accel*/
	ad->label = elm_label_add(ad->grid);
	elm_grid_pack(ad->grid,ad->label,0,0,150,100);
	evas_object_show(ad->label);

	/*Button start*/
	ad->button_start=elm_button_add(ad->grid);
	elm_object_text_set(ad->button_start,"start");
	elm_object_style_set(ad->button_start,"default");
	elm_grid_pack(ad->grid,ad->button_start,20,150,125,50);
	evas_object_show(ad->button_start);

	/* Button end*/
	ad->button_end=elm_button_add(ad->grid);
	elm_object_text_set(ad->button_end,"end");
	elm_object_style_set(ad->button_end,"default");
	elm_grid_pack(ad->grid,ad->button_end,160,150,125,50);
	evas_object_show(ad->button_end);

	/* Show window after base gui is set up */
	evas_object_show(ad->win);

	create_sensor(ad);
}

static bool
app_create(int width, int height, void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */
	appdata_s *ad = data;
	create_base_gui(ad);
	evas_object_smart_callback_add(ad->button_start, "clicked", clicked_start, data);
	evas_object_smart_callback_add(ad->button_end, "clicked", clicked_stop, data);
	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}


static void
watch_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	app_event_get_language(event_info, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
watch_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	watch_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	watch_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED],
		APP_EVENT_LANGUAGE_CHANGED, watch_app_lang_changed, &ad);
	watch_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED],
		APP_EVENT_REGION_FORMAT_CHANGED, watch_app_region_changed, &ad);

	ret = watch_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "watch_app_main() is failed. err = %d", ret);
	}

	return ret;
}

