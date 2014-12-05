/**
 * @file
 * SMS Validation Javascript file
 */
(function($) {

  Drupal.behaviors.smsValidation = {
    attach: function (context, settings) {
      var button = $('#validate-container .form-submit');

      if (button.data('remaining') !== undefined) {
        var remaining = $('#validate-container .form-submit').data('remaining');
        if (remaining < 0) {
          button.prop('disabled', true);

          // start countdown
          // countdown block
          var countdownBlock = $('#countdown-block');

          if (countdownBlock.length == 0) {
            countdownBlock = $('<span id="countdown-block"></span>');
            countdownBlock.html(remaining * -1);
            var timeout = setInterval(function() {
              var currentRemaining = countdownBlock.html();

              if (currentRemaining <= 0) {
                clearTimeout(timeout);
                button.prop('disabled', false);
                countdownBlock.remove();
              }
              else {
                countdownBlock.html(currentRemaining - 1);
              }
            }, 1000);
          }

          button.after(countdownBlock);
        }
        else {
          button.prop('disabled', false)
        }
      }
    }
  };

})(jQuery);
