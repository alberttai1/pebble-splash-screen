#include <pebble.h>
#include <time.h>

// The number of sections of menu 
#define NUM_MENU_SECTIONS 2
// The number of items for first menu 
#define NUM_FIRST_MENU_ITEMS 8
// The number of items for the second menu 
#define NUM_SECOND_MENU_ITEMS 1

Window *my_window;
Window *splash_window; 

TextLayer *text_layer;

// bitmap 
static GBitmap *s_splash_bitmap;
static BitmapLayer *s_splash_bitmap_layer;

// This is just for the main menu selector 
static SimpleMenuLayer *simple_menu_layer;

// Separate the menu into different sections
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

// Each section is composed of a number of menu items
static SimpleMenuItem first_menu_items[NUM_FIRST_MENU_ITEMS];
static SimpleMenuItem second_menu_items[NUM_SECOND_MENU_ITEMS];

// Initialize the variables for the icons on the menu 
static GBitmap *menu_icon_skorea;
static GBitmap *menu_icon_india;
static GBitmap *menu_icon_china;
static GBitmap *menu_icon_mexico;
static GBitmap *menu_icon_germany;
static GBitmap *menu_icon_greece;
static GBitmap *menu_icon_thailand;
static GBitmap *menu_icon_vietnam;

/**
 * This takes care when the user select a menu item on the main menu. It sends it 
 * to the correct spot. 
 * @param index: The index of where we are 
 * @param ctx: Not sure atm 
 */
static void menu_select_callback(int index, void *ctx) {
  // Set the current index to the menu we just pressed
//   currentIndex = index; 
  // Reset the question counter to zero 
//   currentQuestion = 0; 
  // Show the question window 
//   window_stack_push(s_question_window, true);
  
}

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
  s_splash_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH_COLOR);
  s_splash_bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_splash_bitmap_layer, s_splash_bitmap);
  #ifdef PBL_PLATFORM_APLITE
  bitmap_layer_set_compositing_mode(s_splash_bitmap_layer, GCompOpAssign);
  #elif PBL_PLATFORM_BASALT
  bitmap_layer_set_compositing_mode(s_splash_bitmap_layer, GCompOpSet);
  #endif
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_splash_bitmap_layer));  
}
static void splash_window_unload(Window *window)
{
  gbitmap_destroy(s_splash_bitmap);
  bitmap_layer_destroy(s_splash_bitmap_layer);  
}
static void main_window_load(Window *window)
{
  
  // We'll have to load the icon before we can use it
  menu_icon_skorea = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SKOREA_FLAG);
  menu_icon_india = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_INDIA_FLAG);
  menu_icon_china = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CHINA_FLAG);
  menu_icon_mexico = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MEXICO_FLAG);
  menu_icon_germany = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GERMANY_FLAG);
  menu_icon_greece = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GREECE_FLAG);
  menu_icon_thailand = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_THAILAND_FLAG); 
  menu_icon_vietnam = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VIETNAM_FLAG);
  
  // Although we already defined NUM_FIRST_MENU_ITEMS, you can define
  // an int as such to easily change the order of menu items later
  int num_a_items = 0;

  // This is the first section of the menu which is the portion 
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Tikka Masala",
    .subtitle = "0.3 km\n 5/10",
    .callback = menu_select_callback,
    .icon = menu_icon_india,
  };
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Bibimbap",
    .subtitle = "0.4 km",
    .callback = menu_select_callback,
    .icon = menu_icon_skorea, 
  };
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Enchiladas",
    .subtitle = "0.7 km",
    .callback = menu_select_callback,
    .icon = menu_icon_mexico, 
  };
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Chicken Pad Thai",
    .subtitle = "1.1 km",
    .callback = menu_select_callback,
    .icon = menu_icon_thailand, 
  };
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Pho (Beef Noodle Soup)",
    .subtitle = "1.5 km",
    .callback = menu_select_callback,
    .icon = menu_icon_vietnam,
  };
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Hot Pot",
    .subtitle = "2.9 km",
    .callback = menu_select_callback,
    .icon = menu_icon_china,
  };
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Bratwurst Hot Dogs",
    .subtitle = "3.0 km",
    .callback = menu_select_callback,
    .icon = menu_icon_germany,
  };
  first_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Grilled Lamb",
    .subtitle = "4.0 km",
    .callback = menu_select_callback,
    .icon = menu_icon_greece, 
  };

  // This is the second section of the menu 
  second_menu_items[0] = (SimpleMenuItem){
    .title = "About",
    // This call back is for the about rather than question set 
    .callback = menu_select_callback,
//     .callback = special_app_callback,
    .icon = menu_icon_greece, 
  };

  // This is to bind the menu items to the corresponding menu sections
  menu_sections[0] = (SimpleMenuSection){
    // First section 
    .title = "Meal Events",
    .num_items = NUM_FIRST_MENU_ITEMS,
    .items = first_menu_items,
  };
  menu_sections[1] = (SimpleMenuSection){
    // Second section 
    .title = "App",
    .num_items = NUM_SECOND_MENU_ITEMS,
    .items = second_menu_items,
  };

  // Now we prepare to initialize the simple menu layer
  // We need the bounds to specify the simple menu layer's viewport size
  // In this case, it'll be the same as the window's
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Initialize the simple menu layer
  simple_menu_layer = simple_menu_layer_create(bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);

  // Add it to the window for display
  layer_add_child(window_layer, simple_menu_layer_get_layer(simple_menu_layer));
  
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
