#include <pebble.h>
#include <time.h>
  

Window *my_window;
Window *splash_window; 

TextLayer *text_layer;

// bitmap 
static GBitmap *s_splash_bitmap;
static BitmapLayer *s_splash_bitmap_layer;

// This is the timer 
/**
 * This is the function the timer call after the time is up. It will
 * pop the window it is currently on. This is used for the splash screen. 
 * @param data
 */
void timer_callback(void *data) {
  window_stack_pop(true);
}

static void splash_window_load(Window *window)
{
  // Set a 1000 millisecond to load the splash screen
  app_timer_register(1000, (AppTimerCallback) timer_callback, NULL);
  Layer *window_layer = window_get_root_layer(window); 
  s_splash_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH);
  s_splash_bitmap_layer = bitmap_layer_create(GRect(5, 5, 130, 130));
  bitmap_layer_set_bitmap(s_splash_bitmap_layer, s_splash_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_splash_bitmap_layer));  
}
static void splash_window_unload(Window *window)
{
  gbitmap_destroy(s_splash_bitmap);
  bitmap_layer_destroy(s_splash_bitmap_layer);  
}
static void main_window_load(Window *window)
{
  text_layer = text_layer_create(GRect(0, 0, 144, 20));  
  text_layer_set_text(text_layer, "I'm Main Window"); 
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));  
  
}
static void main_window_unload(Window *window)
{
  text_layer_destroy(text_layer);   
}
void handle_init(void) {
  my_window = window_create();
  splash_window = window_create(); 
  window_set_window_handlers(my_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_set_window_handlers(splash_window, (WindowHandlers) {
    .load = splash_window_load,
    .unload = splash_window_unload,
  });
  window_stack_push(my_window, true);
  window_stack_push(splash_window, true);
}

void handle_deinit(void) {
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
