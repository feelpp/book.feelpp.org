// Fix the sidebar under navigation bar.
const sideclass='.sidebar'
const sidewrapclass='.sidebar-container'
const navbarclass='.top-bar'
const headerbarclass = '.header'
const mainclass='.main'

const navbarheight = $( navbarclass ).height();
const fixmeTop = $( sideclass ).position().top;


//var wins = $( window ).width();
//$( sideclass ).css({width: wins*0.2});
//$( sidewrapclass ).css({width: wins*0.2});
//
//$(window).resize(function() { 
//    var wins = $( window ).width();
//    $( sideclass ).css({width: wins*0.2});
//    $( sidewrapclass ).css({width: wins*0.2});
//});

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
