// Fix the sidebar under navigation bar.
const sideclass='.sidebar'
const navbarclass='.top-bar'
const headerbarclass = '.header'

const navbarheight = $( navbarclass ).height();
const fixmeTop = $( sideclass ).position().top;

// Stick sidebar to navbar.
$(window).scroll(function() {                  
    var currentScroll = $(window).scrollTop(); 
    if( currentScroll >= fixmeTop )
    {           
        $(sideclass).css({                    
            position: 'fixed',
            top: navbarheight
        });
    } else {                                  
        $(sideclass).css({                    
            position: 'static'
        });
    }
});
