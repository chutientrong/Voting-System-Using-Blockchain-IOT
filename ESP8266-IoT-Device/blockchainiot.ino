 #include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <SimpleTimer.h>           //https://github.com/jfturcot/SimpleTimer
#include <WiFiClient.h>
//#include <ArduinoJson.h>

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Votting Blockchain System </title>
    <style>
    
    /*
    =====
    CORE STYLES
    =====
    */
    
    .toggle{
      --uiToggleSize: var(--toggleSize, 1.25rem);
      --uiToggleBorderWidth: var(--toggleBorderWidth, 2px);
      --uiToggleColor: var(--toggleColor, #222);
    
      display: var(--toggleDisplay, inline-flex);
      position: relative;
    }
    
    .toggle__input{
      /*
      The pattern by Sara Soueidan https://www.sarasoueidan.com/blog/inclusively-hiding-and-styling-checkboxes-and-radio-buttons/
      */
      width: var(--uiToggleSize);
      height: var(--uiToggleSize);
      opacity: 0;
    
      position: absolute;
      top: 0;
      left: 0;
      margin: 0;
    }
    
    /*
    1. Calculation of the gap for the custom checkbox
    */
    
    .toggle__label{
      display: inline-flex;
      min-height: var(--uiToggleSize);
      padding-left: calc(var(--uiToggleSize) + var(--toggleIndent, .4em));
    }
    
    .toggle__input:not(:disabled) ~ .toggle__label{
      cursor: pointer;
    }
    
    /*
    1. Ems helps to calculate size of the checkbox
    */
    
    .toggle__label::after{
      content: "";
      box-sizing: border-box;  
      width: 1em;
      height: 1em;
      font-size: var(--uiToggleSize); /* 1 */
    
      background-color: transparent;
      border: var(--uiToggleBorderWidth) solid var(--uiToggleColor);
    
      position: absolute;
      left: 0;
      top: 0;
      z-index: 2;
    }
    
    .toggle__input:checked ~ .toggle__label::after{
      background-color: var(--uiToggleColor);
    }
    
    .toggle__text{
      margin-top: auto;
      margin-bottom: auto;
    }
    
    /*
    The arrow size and position depends from sizes of square because I needed an arrow correct positioning from the top left corner of the element toggle
    
    1. Ems helps to calculate size and position of the arrow
    */
    
    .toggle__label::before{
      content: "";
      width: 0;
      height: 0;
      font-size: var(--uiToggleSize); /* 1 */
    
      border-left-width: 0;
      border-bottom-width: 0;
      border-left-style: solid;
      border-bottom-style: solid;
      border-color: var(--toggleArrowColor, #fff);
    
      position: absolute;
      top: .5428em;
      left: .25em;
      z-index: 3;
    
      transform-origin: left top;
      transform: rotate(-40deg) skew(10deg);
    }
    
    .toggle__input:checked ~ .toggle__label::before{
      --uiToggleArrowWidth: var(--toggleArrowWidth, 2px);
    
      width: .4em;
      height: .2em;
      border-left-width: var(--uiToggleArrowWidth);
      border-bottom-width: var(--uiToggleArrowWidth);
    }
    
    /*
    States
    */
    
    /* focus state */
    
    .toggle:focus-within{
      outline: var(--toggleOutlineWidthFocus, 3px) solid var(--toggleOutlineColorFocus, currentColor);
      outline-offset: var(--toggleOutlineOffsetFocus, 5px);
    }
    
    /* disabled state */
    
    .toggle__input:disabled ~ .toggle__label{
      opacity: var(--toggleOpacityDisabled, .24);
      cursor: var(--toggleCursorDisabled, not-allowed);
      user-select: none;
    }
    
    /*
    =====
    PRESENTATION STYLES
    =====
    */
    
    /* 
    The demo skin
    */
    
    .toggle__label::after{
      border-radius: var(--toggleBorderRadius, 2px);
    }
    
    /* 
    The animation of switching states
    */
    
    .toggle__input:not(:disabled) ~ .toggle__label::before{
      will-change: width, height;
      opacity: 0;
    }
    
    .toggle__input:not(:disabled):checked ~ .toggle__label::before{
      opacity: 1;
      transition: opacity .1s ease-out .15s, width .1s ease-out .3s, height .1s ease-out .2s;
    }
    
    .toggle__input:not(:disabled) ~ .toggle__label::after{
      will-change: background-color;
      transition: background-color .15s ease-out;
    }
    
    /*
    =====
    SETTINGS
    =====
    */
    
    .page__custom-settings{
      --toggleColor: #690e90;
      --toggleOutlineColorFocus: #690e90;
      --toggleSize: 2rem;
    }
    
    
    /*
    =====
    DEMO
    =====
    */
    
    body{
      min-height: 100vh;
      margin: 0;    
      font-family: -apple-system, BlinkMacSystemFont, Segoe UI, Roboto, Open Sans, Ubuntu, Fira Sans, Helvetica Neue, sans-serif; 
      background-color: #f0f0f0;
      display: flex;
      flex-direction: column;
    }
    
    .page{
      box-sizing: border-box;
      max-width: 45rem;
      padding: 2.75rem 2rem 2.5rem;
      margin: auto;
      
      background-color: #fff;
      box-shadow: 0 2px 2px 0 rgba(0, 0, 0, .14), 0 3px 1px -2px rgba(0, 0, 0, .12), 0 1px 5px 0 rgba(0, 0, 0, .2);
      border-radius: 2px;
    }
    
    .page__section{
      display: flex;
      flex-wrap: wrap;
      font-weight: 700;
    }
    
    .page__section:nth-child(n+2){
      margin-top: 3rem;
    }
    
    .page__custom-settings{
       --pageToggleTextFontSize: 1.25rem;
    }
    
    .page__name{
      width: 100%;
    }
    
    .page__name::first-letter{
      text-transform: uppercase;
    }
    
    .page__toggle{
      margin-top: 1.25rem;
      margin-right: 1.5rem;
      font-size: var(--pageToggleTextFontSize);
    }
        .header {
            text-align: center;
            background-color: rgb(72, 179, 10);
            color: white;
            padding: 10px;
        }

        .wrapper {
            width: 20%;
            margin: auto;
            border-radius: 8px;
            box-shadow: 0 3px 10px rgb(54, 54, 54);
            overflow: hidden;
        }

        .item {
            padding: 10px;
            margin-left: 40px;
        }

        button {
            display: block;
            margin: 10px auto;
            outline: none;
            padding: 12px;
            border: none;
            background-color: rgb(72, 179, 10);
            border-radius: 8px;
            color: white;
            cursor: pointer;
            width: 150px;
        }

        .result {
            text-align: center;
            margin-top: 20px;
        }
    </style>
</head>

<body>
    <div class="wrapper">
        <div class="header">
            <h3>Voting Blockchain</h3>
        </div>
        <div class="page">
        <div id="itemForm">
          <form action="/action_page">
            <div class="page__section page__custom-settings">
              <span class="page__name">Vote</span>
              <div class="page__toggle">
                <label class="toggle">
                  <input class="toggle__input" type="checkbox" value="Nguyen Van A" name = "cb1" checked>
                  <span class="toggle__label">
                    <span class="toggle__text">Nguyen Van A</span>
                  </span>
                </label>
              </div>
              <div class="page__toggle">
                <label class="toggle">
                  <input class="toggle__input" type="checkbox" value="Nguyen Van B" name = "cb2">
                  <span class="toggle__label">
                    <span class="toggle__text">Nguyen Van B</span>
                  </span>
                </label>
              </div>
              <div class="page__toggle">
                <label class="toggle">
                  <input class="toggle__input" type="checkbox" value="Nguyen Van C" name = "cb3">
                  <span class="toggle__label">
                    <span class="toggle__text">Nguyen Van C</span>
                  </span>
                </label>
              </div>
              <div class="page__toggle">
                <label class="toggle">
                  <input class="toggle__input" type="checkbox" value="Nguyen Van D" name = "cb4">
                  <span class="toggle__label">
                    <span class="toggle__text">Nguyen Van D</span>
                  </span>
                </label>
              </div>
              <button id="submit" type="submit" value="Submit">Save</button>
            </form>
          </div>
        </div>
</body>

</html>
)=====";
//
//const char LOADING_page[] PROGMEM = R"=====(
//<!DOCTYPE html>
//<html lang="en">
//
//<head>
//    <meta charset="UTF-8">
//    <meta http-equiv="X-UA-Compatible" content="IE=edge">
//    <meta name="viewport" content="width=device-width, initial-scale=1.0">
//    <title>Votting Blockchain System </title>
//    <style type="text/css">
//
//        .page__custom-settings{
//            --toggleColor: #690e90;
//            --toggleOutlineColorFocus: #690e90;
//            --toggleSize: 2rem;
//        }
//
//        body{
//            min-height: 100vh;
//            margin: 0;    
//            font-family: -apple-system, BlinkMacSystemFont, Segoe UI, Roboto, Open Sans, Ubuntu, Fira Sans, Helvetica Neue, sans-serif; 
//            background-color: #f0f0f0;
//            display: flex;
//            flex-direction: column;
//        }
//
//        .page{
//            box-sizing: border-box;
//            max-width: 45rem;
//            padding: 2.75rem 2rem 2.5rem;
//            margin: auto;
//
//            background-color: #fff;
//            box-shadow: 0 2px 2px 0 rgba(0, 0, 0, .14), 0 3px 1px -2px rgba(0, 0, 0, .12), 0 1px 5px 0 rgba(0, 0, 0, .2);
//            border-radius: 2px;
//        }
//
//        .page__section{
//            display: flex;
//            flex-wrap: wrap;
//            font-weight: 700;
//        }
//
//        .page__section:nth-child(n+2){
//            margin-top: 3rem;
//        }
//
//        .page__custom-settings{
//            --pageToggleTextFontSize: 1.25rem;
//        }
//
//        .page__name{
//            width: 100%;
//        }
//
//        .page__name::first-letter{
//            text-transform: uppercase;
//        }
//
//        .page__toggle{
//            margin-top: 1.25rem;
//            margin-right: 1.5rem;
//            font-size: var(--pageToggleTextFontSize);
//        }
//        .header {
//            text-align: center;
//            background-color: #f82121;
//            color: white;
//            padding: 10px;
//        }
//
//        .wrapper {
//            width: 20%;
//            margin: auto;
//            border-radius: 8px;
//            box-shadow: 0 3px 10px rgb(54, 54, 54);
//            overflow: hidden;
//        }
//
//        .item {
//            padding: 10px;
//            margin-left: 40px;
//        }
//
//        input[type=text]{
//            width:100%;
//            border:2px solid #aaa;
//            border-radius:4px;
//            margin:8px 0;
//            outline:none;
//            padding:8px;
//            box-sizing:border-box;
//            transition:.3s;
//        }
//
//        input[type=text]:focus{
//            border-color:dodgerBlue;
//            box-shadow:0 0 8px 0 dodgerBlue;
//        }
//
//        h5{
//            color: #dc4343;
//        }
//        h6{
//            color: #dc4343;
//        }
//
//        .loading {
//            display: block;
//            margin: 0 auto;
//            border: 8px solid #f82121;
//            border-top-color: #b32727;
//            border-bottom-color: #ffffff;
//            border-radius: 100%;
//            width: 80px;
//            height: 80px;
//            -webkit-animation: spin infinite 1s linear;
//            animation: spin infinite 1s linear;
//        }
//
//        @keyframes spin {
//            from {
//                transform: rotate(0deg);
//            }
//            to {
//                transform: rotate(360deg);
//            }
//        }
//
//        @-webkit-keyframes spin {
//            from {
//                -webkit-transform: rotate(0deg);
//            }
//            to {
//                -webkit-transform: rotate(360deg);
//            }
//        }
//
//    </style>
//
//</head>
//
//<body>
//
//      <div class="wrapper">
//        <div class="header">
//            <h3>Voting Blockchain</h3>
//        </div>
//        <div class="page">
//        <div id="itemForm">
//          <form action="/action_page">
//            <div class="page__section page__custom-settings">
//
//              <div class="loading"></div>
//
//              <div class="page__toggle">
//                <label class="toggle">
//                    <!-- <h6>Device token not available</h6>
//                    <h6>Please update your device token</h6> -->
//                    <!-- <input type="text" placeholder="Device Token"> -->
//                  <span class="toggle__label">
//                    <!-- <span class="toggle__text">Nguyen Van D</span> -->
//                    <h5>Device token not available</h5>
//                    <h6>Please update your device token</h6>
//                  </span>
//                </label>
//              </div>
//              <!-- <button id="submit" type="submit" value="Submit">Change</button> -->
//            </form>
//          </div>
//        </div>
//        <div class="center"></div>
//</body>
//
//</html>
//)=====";
//SSID and Password of your WiFi router
const char* ssid = "3/36";
const char* password = "Hoilamgi";

//const char* ssid = "UIT Public";
//const char* password = "";
const char* device_token = "19f823a5";
ESP8266WebServer server(2000); //Server on port 2000

//************************************************************************
String getData, Link;
String URL = "http://192.168.1.74:8000/blockchainiot/getdata.php/"; //computer IP or the server domain
//************************************************************************

WiFiClient client;

bool CheckDevice(){

  if(WiFi.isConnected()){

    HTTPClient http;    //Declare object of class HTTPClient
    //GET Data
    getData =  "?device_token=" + String(device_token); 
    //GET methode
    Link = URL + getData;
    http.begin(client,Link); //initiate HTTP request,
    
    int httpCode = http.GET();   //Send the request
    String payload = http.getString();    //Get the response payload
    
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    if(payload == "1"){
      return true;
    }else 
    {
      return false;  
    }
  }
  
}
int SendDatatoBlockchain( String a, String b, String c, String d ){
  Serial.println("Sending the Data to Blockchain");
  if(WiFi.isConnected()){
//      WiFiClient client;
      HTTPClient http;
      String serverName = "http://192.168.1.74:3000/mine";
//      String serverName = "http://10.45.186.133:3000/mine";
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/json");
      // Data to send with HTTP POST
      String httpRequestData = "{\"data\":\"DeviceID: "+String(device_token)+","+a+","+b+","+c+","+d+"\"}";           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
      return httpResponseCode;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    return 0;
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================



void handleRoot() {
//  bool cd=CheckDevice();
//  if(cd == true){
//    String s = MAIN_page; //Read HTML contents
//    server.send(200, "text/html", s); //Send web page
//  }
//  else{
//    String s = LOADING_page; //Read HTML contents
//    server.send(200, "text/html", s); //Send web page
//  }
    String s = MAIN_page; //Read HTML contents
    server.send(200, "text/html", s); //Send web page
}
//===============================================================
// This routine is executed when you press submit
//===============================================================
void handleForm() {
  String cb1 = server.arg("cb1"); 
  String cb2 = server.arg("cb2"); 
  String cb3 = server.arg("cb3"); 
  String cb4 = server.arg("cb4"); 
  Serial.print("CB1:");
  Serial.println(cb1);
  Serial.print("CB2:");
  Serial.println(cb2);
  Serial.print("CB3:");
  Serial.println(cb3);
  Serial.print("CB4:");
  Serial.println(cb4);

  bool cd = CheckDevice();
  if(cd == true){
    int rp = SendDatatoBlockchain(cb1,cb2,cb3,cb4);
     if(rp==302){
     String s = "<script> alert('Vote thanh cong!');location.href = \"/\"</script>";
     server.send(200, "text/html", s); //Send web page
     }
     else{
      String s = "<script> alert('Vote khong thanh cong!');location.href = \"/\"</script>";
     server.send(200, "text/html", s); //Send web page
     }
  }else{
    String s = "<script> alert('Ma thiet bi khong dung voi co so du lieu, hay cap nhat lai!');location.href = \"/\"</script>";
     server.send(200, "text/html", s); //Send web page
  }
}

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/action_page", handleForm); //form action is handled here
//  server.on("/action_page2", handleForm2); //form action is handled here

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
