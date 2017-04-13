// key value arg to modify the image.
// e.g :
// cover({ bgcolor:"red"
//         title1:"toto" })
var cover = function( kv={} ) {
    svgname="/images/book_cover_simple.svg"
    xhr = new XMLHttpRequest();
    xhr.open("GET",svgname,false);
    xhr.overrideMimeType("image/svg+xml");
    xhr.send("");
    svg = xhr.responseXML.documentElement;
    if( kv.bgcolor != null ) {
        elt = svg.getElementById("svg_book_bg");
        elt.style.fill=kv.bgcolor;
    }
    if( kv.bgbandcolor != null ) {
        elt = svg.getElementById("svg_book_bg_band");
        elt.style.fill=kv.bgbandcolor;
    }
    if( kv.title0 != null ) {
        elt = svg.getElementById("svg_book_text_title");
        elt.childNodes[0].childNodes[0].textContent = kv.title0;
    }
    if( kv.title1 != null ) {
        elt = svg.getElementById("svg_book_text_title");
        elt.childNodes[1].childNodes[0].textContent = kv.title1;
    }
    if( kv.subtitle != null ) {
        elt = svg.getElementById("svg_book_text_subtitle");
        elt.childNodes[0].childNodes[0].textContent = kv.subtitle;
    }
    if( kv.id != null ) {
        document.getElementById(kv.id).appendChild(svg);
    }
}
