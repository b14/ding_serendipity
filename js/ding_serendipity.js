(function ($) {
  
  $.fn.ding_serendipity_load = function( options ) {  
    // Create some defaults, extending them with any options that were provided
    var settings = $.extend( {
    }, options),
    $this = $(this);
    
    return this.each(function() {
      $('.pager a', $this).each(function() {
        $(this).click(function(e) {
          e.preventDefault();
          
          var $href = $(this).attr('href'),
            $path = 'ding/serendipity/fetch',
            $values = $href.split('/'),
            $settings = {
              id: $values[0],
              offset: $values[1],
              length: $values[2]
            };
          
          var updateContent = function(data) {
            // The data parameter is a JSON object. The “products” property is the list of products items that was returned from the server response to the ajax request.
            $('.ding-list-content', $this).html(data.products);
          }
          $.ajax({
            type: 'POST',
            url: $path, // Which url should be handle the ajax request. This is the url defined in the <a> html tag
            success: updateContent, // The js function that will be called upon success request
            dataType: 'json', //define the type of data that is going to get back from the server
            data: $settings //Pass a key/value pair
          });
        });
      });
    }).addClass('dingSerendipityLink-processed');
  };
  
  Drupal.behaviors.ding_serendipity = {
    attach: function (context, settings) {
      $('.ding_serendipity_load:not(.dingSerendipityLink-processed)', context).ding_serendipity_load();
    }
  };
})(jQuery);
