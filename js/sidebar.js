// Fix the sidebar under navigation bar.
const sideclass='.sidebar'
const navbarclass='.top-bar'
var fixmeTop = $( sideclass ).position().top;       // get initial position of the element
var navbarheight = $( navbarclass ).height();
$(window).scroll(function() {                  // assign scroll event listener
    var currentScroll = $(window).scrollTop(); // get current position

    if (currentScroll >= fixmeTop) {           // apply position: fixed if you
        $(sideclass).css({                      // scroll to that element or below it
            position: 'fixed',
            top: navbarheight,
            left: '0',
        });
    } else {                                   // apply position: static
        $(sideclass).css({                      // if you scroll above it
            position: 'static'
        });
    }
});
