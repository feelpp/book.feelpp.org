// key value arg to modify the image.
// e.g :
// cover({ bgcolor:"red"
//         title:"toto" })
var cover = function( kv={} ) {
    svgname="./images/book_cover_simple.svg"

    div = document.createElement("div");
    div.setAttribute("id","cover");
    document.body.appendChild(div);
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
    if( kv.title != null ) {
        elt = svg.getElementById("svg_book_text_title");
        elt.childNodes[0].childNodes[0].textContent = kv.title;
    }
    if( kv.subtitle != null ) {
        elt = svg.getElementById("svg_book_text_subtitle");
        elt.childNodes[0].childNodes[0].textContent = kv.subtitle;
    }
    document.getElementById("cover").appendChild(svg);
}
