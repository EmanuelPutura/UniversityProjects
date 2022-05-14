$(document).ready(function() {
    $(".dialog-window").hide();

    $("#show-dialog-btn").click(function(){
        $(".dialog-window").show();
    });
   
    $(".close-btn").click(function(){
        $(".dialog-window").hide();
    });

    var dialogBox = null;
    var relativeX = null; // the left distance between the cursor and the title div
    var relativeY = null; // the top distance between the cursor and the title div

    $(this).on({
        mouseup: function(event) {
            if (dialogBox) {
                dialogBox.css("background-color", "#f1f1f1");
                dialogBox = null;
            }
        },
    });

    $(".dialog-window-header").on({
        mousedown: function(event) {
            dialogBox = $(this).parent();
            dialogBox.css("background-color", "#d5d5d5");

            var dialogPosition = dialogBox.offset(); // the (left, top) distance between parent and top left corner 
 
            /*
                event.pageX, event.pageY - the coordinates of the location on the dialog box where the mousedown event occurred
                dialogPosition.left, dialogPosition.right - the coordinates of the dialog box (before the movement is initiated)
                relativeX, relativeY - needed when moving the dialog box, the change of coordinates is performed with respect to the click location and the initial click offset 
            */
            relativeX = event.pageX - dialogPosition.left;
            relativeY = event.pageY - dialogPosition.top;
        },

        mousemove: function(event) {
            if (dialogBox) {
                dialogBox.offset({
                    top: event.pageY - relativeY,
                    left: event.pageX - relativeX
                });
            }
        },

        mouseup: function(event) {
            dialogBox.css("background-color", "#f1f1f1");
            dialogBox = null;
        },
    });
});
