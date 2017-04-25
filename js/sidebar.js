// Fix the sidebar under navigation bar.
const sideclass='.sidebar'
const sidewrapclass='.sidebar-container'
const navbarclass='.top-bar'
const headerbarclass = '.header'
const mainclass='.main'
const footerclass='footer'

const navbarheight = $( navbarclass ).height();
const fixmeTop = $( sideclass ).position().top;


var rmSideBar = function() {
    var winw = $( window ).width();
    if( winw < 1000 ) {
        $( sidewrapclass ).css({
            display: 'none'
        });
        $( mainclass ).css({
            width: '100%'
        });
        $( footerclass ).css({
            width: '100%'
        });
    }
    else {
        $( sidewrapclass ).css({
            display: 'initial'
        });
        $( mainclass ).css({
            width: '80%'
        });
        $( footerclass ).css({
            width: '80%'
        });
    }
}

rmSideBar();

// Remove side bar for small window.
$(window).resize(function() { 
    rmSideBar();
});

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



