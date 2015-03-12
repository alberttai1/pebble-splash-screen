#include <pebble.h>

Window *my_window;
Window *splash_window; 

TextLayer *text_layer;

static void splash_window_load(Window *window)
{
  
}
static void splash_window_unload(Window *window)
{
  
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
}

void handle_deinit(void) {
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
