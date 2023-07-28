#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/elements.h>
#include <gui/view_dispatcher.h>
#include <input/input.h>
#include <storage/storage.h>
#include <dialogs/dialogs.h>
#include <stream/stream.h>

#include <stdlib.h>

#include "confirm_dotkiller.h"

#include "assets_icons.h"
#include "macos_dotkiller_icons.h"
// some icons in my /images folder, are also in the standard assets this is why i included both but maybe just mine (the second) it would be ok	

#define STORAGE_EXT_PATH_PREFIX "/ext"
// this line is also defined in "storage.h" but better to be sure :)

static bool dotkiller_enabled = false;
static bool confirm_removal = false;

void remove_hidden_files() {
    Storage storage;
    StorageEntry entry;
    StorageIterator iterator;

    storage_init(&storage);

    storage_iterator_init(&iterator, STORAGE_EXT_PATH_PREFIX);

    while (storage_iterator_next(&iterator, &entry) == StorageIteratorStatusOk) {
        if (strstr(entry.name, "._") == entry.name) {
            char full_path[256];
            snprintf(full_path, sizeof(full_path), "%s/%s", STORAGE_EXT_PATH_PREFIX, entry.name);

            storage_common_remove(&storage, full_path);
        }
    }

    storage_iterator_close(&iterator);

    storage_deinit(&storage);
}

static void dotkill_input_callback(InputEvent* event, void* context) {
    UNUSED(context);

    if (event->type == EventTypeKey && event->input.type == InputTypePress) {
        switch (event->input.key) {
            case InputKeyUp:
            case InputKeyDown:
            case InputKeyRight:
            case InputKeyLeft:
                break;

            case InputKeyOk:
                dotkiller_enabled = true;
                show_confirmation_screen();
                break;

            case InputKeyBack:
                view_dispatcher_stop((ViewDispatcher*)context);
                break;

            default:
                break;
        }
    }
}

static void dotkill_render_callback(Canvas* canvas, void* context) {
    UNUSED(canvas);
    UNUSED(context);
    canvas_draw_frame(canvas, 0, 0, 128, 64);
	canvas_draw_box(canvas, 6, 6, 5, 14);
	canvas_draw_box(canvas, 12, 6, 4, 2);
	canvas_draw_box(canvas, 14, 8, 4, 2);
	canvas_draw_box(canvas, 16, 10, 4, 6);
	canvas_draw_box(canvas, 10, 18, 6, 2);
	canvas_draw_box(canvas, 14, 16, 4, 2);
	canvas_draw_box(canvas, 41, 5, 4, 13);
	canvas_draw_box(canvas, 39, 7, 2, 4);
	canvas_draw_box(canvas, 44, 7, 4, 4);
	canvas_draw_box(canvas, 43, 17, 4, 3);
	canvas_draw_dot(canvas, 42, 18);
	canvas_draw_box(canvas, 50, 6, 4, 14);
	canvas_draw_box(canvas, 52, 12, 6, 2);
	canvas_draw_box(canvas, 56, 10, 6, 2);
	canvas_draw_box(canvas, 58, 7, 4, 3);
	canvas_draw_box(canvas, 53, 16, 9, 2);
	canvas_draw_box(canvas, 58, 17, 4, 3);
	canvas_draw_box(canvas, 53, 15, 6, 2);
	canvas_draw_frame(canvas, 1, 1, 126, 62);
	canvas_draw_box(canvas, 65, 18, 8, 2);
	canvas_draw_box(canvas, 67, 9, 4, 9);
	canvas_draw_box(canvas, 65, 8, 8, 2);
	canvas_draw_box(canvas, 67, 4, 4, 3);
	canvas_draw_box(canvas, 75, 5, 4, 13);
	canvas_draw_box(canvas, 77, 18, 8, 2);
	canvas_draw_box(canvas, 81, 16, 4, 2);
	canvas_draw_box(canvas, 86, 5, 4, 13);
	canvas_draw_box(canvas, 88, 18, 8, 2);
	canvas_draw_box(canvas, 92, 16, 4, 2);
	canvas_draw_circle(canvas, 29, 12, 7);
	canvas_draw_circle(canvas, 29, 12, 6);
	canvas_draw_circle(canvas, 29, 12, 5);
	canvas_draw_dot(canvas, 25, 7);
	canvas_draw_dot(canvas, 24, 8);
	canvas_draw_dot(canvas, 24, 16);
	canvas_draw_dot(canvas, 25, 17);
	canvas_draw_dot(canvas, 33, 7);
	canvas_draw_dot(canvas, 34, 8);
	canvas_draw_dot(canvas, 34, 16);
	canvas_draw_dot(canvas, 33, 17);
	canvas_draw_circle(canvas, 29, 12, 4);
	canvas_draw_dot(canvas, 25, 10);
	canvas_draw_dot(canvas, 27, 8);
	canvas_draw_dot(canvas, 31, 8);
	canvas_draw_dot(canvas, 33, 10);
	canvas_draw_dot(canvas, 25, 14);
	canvas_draw_dot(canvas, 33, 14);
	canvas_draw_dot(canvas, 31, 16);
	canvas_draw_dot(canvas, 27, 16);
	canvas_draw_dot(canvas, 13, 17);
	canvas_draw_dot(canvas, 12, 17);
	canvas_draw_dot(canvas, 13, 8);
	canvas_draw_dot(canvas, 12, 8);
	canvas_draw_line(canvas, 15, 10, 15, 17);
	canvas_draw_dot(canvas, 11, 17);
	canvas_draw_dot(canvas, 11, 7);
	canvas_draw_dot(canvas, 11, 8);
	canvas_draw_dot(canvas, 11, 6);
	canvas_draw_box(canvas, 97, 5, 4, 15);
	canvas_draw_box(canvas, 98, 5, 9, 2);
	canvas_draw_box(canvas, 103, 6, 4, 3);
	canvas_draw_box(canvas, 99, 12, 5, 2);
	canvas_draw_box(canvas, 99, 18, 9, 2);
	canvas_draw_box(canvas, 104, 17, 4, 1);
	canvas_draw_box(canvas, 110, 6, 4, 14);
	canvas_draw_box(canvas, 112, 10, 10, 2);
	canvas_draw_box(canvas, 118, 6, 4, 4);
	canvas_draw_box(canvas, 110, 6, 12, 2);
	canvas_draw_line(canvas, 113, 12, 119, 18);
	canvas_draw_line(canvas, 113, 13, 119, 19);
	canvas_draw_line(canvas, 114, 12, 120, 18);
	canvas_draw_box(canvas, 120, 16, 3, 4);
	canvas_draw_icon(canvas, 57, 22, &I_Space_65x18);
	canvas_draw_icon(canvas, 57, 42, &I_Space_65x18);
	canvas_set_font(canvas, FontPrimary);
	canvas_draw_str(canvas, 82, 34, "Clean");
	canvas_set_font(canvas, FontPrimary);
	canvas_draw_str(canvas, 87, 54, "Exit");
	canvas_draw_icon(canvas, 74, 46, &I_Pin_back_arrow_10x8);
	canvas_draw_icon(canvas, 70, 26, &I_Ok_btn_9x9);
	extern const Icon I_Target_40x40;
	canvas_draw_icon(canvas, 10, 20, &I_Target_40x40);
	canvas_draw_icon(canvas, 10, 20, &I_Target_40x40);

}

int32_t flipper_dotkiller_app(void* p) {
    UNUSED(p);
    InputEvent event;
    ViewDispatcher* view_dispatcher = view_dispatcher_alloc();
    ViewPort* view_port = view_port_alloc();

    view_port_draw_callback_set(view_port, dotkill_render_callback, NULL);
    view_port_input_callback_set(view_port, dotkill_input_callback, view_dispatcher);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    while (1) {
        furi_check(furi_message_queue_get(gui->message_queue, &event, FuriWaitForever) == FuriStatusOk);
        view_dispatcher_run(view_dispatcher);
    }

    view_dispatcher_free(view_dispatcher);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    return 0;
}
