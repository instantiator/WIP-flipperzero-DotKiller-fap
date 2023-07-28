#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <storage/storage.h>
#include <gui/elements.h>
#include <dialogs/dialogs.h>
#include <stream/stream.h>

#include <stdlib.h>

#include "confirm_dotkiller.h"

#include "macos_dotkiller_icons.h"

static void confirm_input_callback(InputEvent* event, void* context) {
    UNUSED(context);

    if (event->type == EventTypeKey && event->input.type == InputTypePress) {
        switch (event->input.key) {
            case InputKeyLeft:
                confirm_removal = false;
                break;

            case InputKeyRight:
    			confirm_removal = true;
    			remove_hidden_files();
    			break;
            
            case InputKeyBack:
                confirm_removal = false;
                break;

            default:
                break;
        }
    }
}

static void confirm_render_callback(Canvas* canvas, void* context) {
    UNUSED(canvas);
    UNUSED(context);
    canvas_draw_icon(canvas, 2, 55, &I_ButtonLeft_4x7);
	canvas_draw_icon(canvas, 122, 55, &I_ButtonRight_4x7);
	canvas_draw_line(canvas, 1, 51, 128, 51);
	canvas_set_font(canvas, FontPrimary);
	canvas_draw_str(canvas, 9, 62, "No");
	canvas_set_font(canvas, FontPrimary);
	canvas_draw_str(canvas, 99, 62, "Yes");
	canvas_set_font(canvas, FontPrimary);
	canvas_draw_str(canvas, 53, 11, "Confirmation:");
	canvas_draw_icon(canvas, 2, 7, &I_WarningDolphin_45x42);
	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 55, 22, "Are you sure to");
	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 50, 31, "delete the useless");
	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 51, 40, "hiddenfiles in your");
	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 48, 49, "external SD card?");
	canvas_draw_icon(canvas, 85, 54, &I_SDcardMounted_11x8);
	canvas_draw_icon(canvas, 2, 3, &I_unknown_10px);
	canvas_draw_icon(canvas, 36, 54, &I_Pin_back_arrow_10x8);
	canvas_set_font(canvas, FontPrimary);
	canvas_draw_str(canvas, 49, 62, "Back");
}

void show_confirmation_screen() {
    InputEvent event;
    ViewDispatcher* view_dispatcher = view_dispatcher_alloc();
    ViewPort* view_port = view_port_alloc();

    view_port_draw_callback_set(view_port, confirm_render_callback, NULL);
    view_port_input_callback_set(view_port, confirm_input_callback, view_dispatcher);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    while (confirm_removal == false) {
        furi_check(furi_message_queue_get(gui->message_queue, &event, FuriWaitForever) == FuriStatusOk);
        view_dispatcher_run(view_dispatcher);
    }

    view_dispatcher_free(view_dispatcher);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);
    
    return;
}
