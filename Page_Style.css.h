#ifndef PAGE_STYLE_CSS_H
#define PAGE_STYLE_CSS_H

const char PAGE_Style_css[] PROGMEM = R"=====(
hr {
    background-color: #eee;
    border: 0 none;
    color: #eee;
    height: 1px;
}
.btn, .btn:link, .btn:visited {
    border-radius: 0.3em;
    border-style: solid;
    border-width: 1px;
    color: #111;
    display: inline-block;
    font-family: avenir, helvetica, arial, sans-serif;
    letter-spacing: 0.15em;
    margin-bottom: 0.5em;
    padding: 1em 0.75em;
    text-decoration: none;
    text-transform: uppercase;
    -webkit-transition: color 0.4s, background-color 0.4s, border 0.4s;
    transition: color 0.4s, background-color 0.4s, border 0.4s;
}
.btn:hover, .btn:focus {
    color: #DFE0DF;
    border: 1px solid #DFE0DF;
    -webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;
    transition: background-color 0.3s, color 0.3s, border 0.3s;
}
.btn:active {
    color: #FF8C00;
    border: 1px solid #FF8C00;
    -webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;
    transition: background-color 0.3s, color 0.3s, border 0.3s;
}
.btn--s{
    font-size: 12px;
}
.btn--m {
    font-size: 14px;
}
.btn--l {
    font-size: 20px;
    border-radius: 0.25em !important;
}
.btn--full, .btn--full:link {
    border-radius: 0.25em;
    display: block;
    margin-left: auto;
    margin-right: auto;
    text-align: center;
    width: 100%;
}
.btn--orange:link, .btn--orange:visited {
    color: #fff;
    background-color: #FF8C00;
}
.btn--orange:hover, .btn--orange:focus {
    color: #fff !important;
    background-color: #643E1C;
    border-color: #643E1C;
}
.btn--orange:active {
    color: #fff;
    background-color: #402E32;
    border-color: #402E32;
}
@media screen and (min-width: 32em) {
    .btn--full {
        max-width: 16em !important;
    }
}
)=====";

#endif
