//Homepage 
 const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Taupunkttemperatur Steuerung</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <!----------------------------CSS---------------------------->
  
<style>


  input{background:#f1f1f1;
    border:0;
    width: 40%;
    height: 44px;
    padding:0 15px
  }
 
  input[type=number]{
    background:#f1f1f1;border:0;padding:0 15px
    width:100%;
    height:44px;
    border-radius:4px;
    margin:10px auto;
    font-size:15px
  }
  
  button{
    background:#f1f1f1;border:0;padding:0 15px
    width:100%;
    height:44px;
    border-radius:4px;
    margin:10px auto;
    font-size:15px
  }
  
  body{
    background:#3498db;
    font-family:sans-serif;
    font-size:14px;color:#777
    }
    


    
  form{
    background:#fff;
    margin:2px auto;
    padding:8px;
    border-radius:5px;
    text-align:center
    }
    
  .box{
    background:#fff;max-width:350px;
    margin:2px auto;
    padding:8px;
    border-radius:5px;
    text-align:center
    }
    
  .csshand{
    background:#3498db;
    color:#fff;
    cursor:pointer    
    }

  .btn{
    background:#3498db;
    color:#fff;
    cursor:pointer
 
    }
  #wertetabel {
            
           border:3px solid #3498db;
           
    } 


  #wertetabel  tr,  td{
            
           max-width:350px;
      
    }

  #wertetabel    th {
            background-color: #3498db;
            max-width:350px;
            border:3px solid #3498db;
    }
#wertetabel tr:nth-child(even){background-color: #f2f2f2;}

#wertetabel tr:hover {background-color: #ddd;}

  }
</style>


  <!-------------------------JavaScrip------------------------->
  <script>
    //Json Object Dekleration
    var obj = {};
    //Interval aufrufe 
    setInterval(function()
    {
      Werte();
    }, 1000);
    //-------------------------------------------------------
    function Werte()
    {
      var Request = new XMLHttpRequest();
      Request.onreadystatechange = function()
      {
        if(this.readyState == 4 && this.status == 200)
        {
          //Werte von Respons in Json Object Parsen
          obj = JSON.parse(this.responseText);
          console.log(obj);
          //Wert in Html Element schreiben
          document.getElementById("type_obj0").innerHTML = obj[0].type;
          document.getElementById("value_obj0").innerHTML = obj[0].value;  
          document.getElementById("unit_obj0").innerHTML = obj[0].unit;  

                    //Wert in Html Element schreiben
          document.getElementById("type_obj1").innerHTML = obj[1].type;
          document.getElementById("value_obj1").innerHTML = obj[1].value;  
          document.getElementById("unit_obj1").innerHTML = obj[1].unit;  
                    //Wert in Html Element schreiben
          document.getElementById("type_obj2").innerHTML = obj[2].type;
          document.getElementById("value_obj2").innerHTML = obj[2].value;  
          document.getElementById("unit_obj2").innerHTML = obj[2].unit;  
                    //Wert in Html Element schreiben
          document.getElementById("type_obj3").innerHTML = obj[3].type;
          document.getElementById("value_obj3").innerHTML = obj[3].value;  
          document.getElementById("unit_obj3").innerHTML = obj[3].unit;  
        
                            //Wert in Html Element schreiben
          document.getElementById("type_obj4").innerHTML = obj[4].type;
          document.getElementById("value_obj4").innerHTML = obj[4].value;  
          document.getElementById("unit_obj4").innerHTML = obj[4].unit;  
                            //Wert in Html Element schreiben
          document.getElementById("type_obj5").innerHTML = obj[5].type;
          document.getElementById("value_obj5").innerHTML = obj[5].value;  
          document.getElementById("unit_obj5").innerHTML = obj[5].unit;  
                            //Wert in Html Element schreiben
          document.getElementById("type_obj6").innerHTML = obj[6].type;
          document.getElementById("value_obj6").innerHTML = obj[6].value;  
          document.getElementById("unit_obj6").innerHTML = obj[6].unit;  
                            //Wert in Html Element schreiben
          document.getElementById("type_obj7").innerHTML = obj[7].type;
          document.getElementById("value_obj7").innerHTML = obj[7].value;  
          document.getElementById("unit_obj7").innerHTML = obj[7].unit; 
                            //Wert in Html Element schreiben
          document.getElementById("type_obj8").innerHTML = obj[8].type;
          document.getElementById("value_obj8").innerHTML = obj[8].value;  
          document.getElementById("unit_obj8").innerHTML = obj[8].unit;   
                            //Wert in Html Element schreiben
          document.getElementById("type_obj9").innerHTML = obj[9].type;
          document.getElementById("value_obj9").innerHTML = obj[9].value;  
          document.getElementById("unit_obj9").innerHTML = obj[9].unit;   

          //Luefterstatus 

          if ( obj[10].value === 1){
            document.getElementById("csshand").style.backgroundColor = "green";
          }
          else{
            
            document.getElementById("csshand").style.backgroundColor = "#3498db";
            
            }
          
          
        }
      };
      Request.open("GET", "env", true);
      Request.send();
    }
    
    //Hand setzen momenta nicht in verwendung.
function hand(value)
 {    var Request = new XMLHttpRequest();
      var url = "hand";
      var para = "hand=" + value;
      Request.open("GET", "hand?"+para, true);
      Request.send();
      
 }
  </script>
  <!----------------------------HTML--------------------------->
  </head><body>



  <div class="box">
  <table align="center" id="wertetabel">
  <tr>
    <th>Type</th>
    <th>Value</th>
    <th>Unit</th>
  </tr>
  <tr>
    <td id="type_obj0"></td>
    <td id="value_obj0"></td>
    <td id="unit_obj0"></td>
  </tr>
  <tr>
    <td id="type_obj1"></td>
    <td id="value_obj1"></td>
    <td id="unit_obj1"></td>
  </tr>
  <tr>
    <td id="type_obj2"></td>
    <td id="value_obj2"></td>
    <td id="unit_obj2"></td>
  </tr>
  <tr>
    <td id="type_obj3"></td>
    <td id="value_obj3"></td>
    <td id="unit_obj3"></td>
  </tr>
  <tr>
    <td id="type_obj4"></td>
    <td id="value_obj4"></td>
    <td id="unit_obj4"></td>
  </tr>
  
  <tr>
    <td id="type_obj5"></td>
    <td id="value_obj5"></td>
    <td id="unit_obj5"></td>
  </tr>
  <tr>
    <td id="type_obj6"></td>
    <td id="value_obj6"></td>
    <td id="unit_obj6"></td>
  </tr>
  <tr>
    <td id="type_obj7"></td>
    <td id="value_obj7"></td>
    <td id="unit_obj7"></td>
  </tr>
  <tr>
    <td id="type_obj8"></td>
    <td id="value_obj8"></td>
    <td id="unit_obj8"></td>
  </tr>
  <tr>
    <td id="type_obj9"></td>
    <td id="value_obj9"></td>
    <td id="unit_obj9"></td>
  </tr>

</table>

  </div>
  

  <div class="box">
        
     <button id="csshand" class="btn" onclick="hand(true)">Hand Ein</button>
     
     <button id="csshand" class="btn" onclick="hand(false)">Hand Aus</button>

  </div>   



     
  <div class="box">
    Differenz:
  <form action="/get">
  <input type="number" name="diff" >
  <input type="submit" class=btn value="Werte setzen">
  </form>
 
  </div>

  <div class="box">
    Start Luftfeuchte:
  <form action="/get">
  <input type="number" name="starthumi" >
  <input type="submit" class=btn value="Werte setzen">
  </form>


  <div class="box">
    Min. Innentemperatur:
  <form action="/get">
  <input type="number" name="MinTemp" >
  <input type="submit" class=btn value="Werte setzen">
  </form>
 
  </div>

  

  <div class="box">

    <form action="/firmware"  accept-charset="utf-8">
    <input type='submit' class="btn" value='Firmware Update'>
    </form>

  </div>   

  
   

</body></html>)rawliteral";



/* Style */
String style =
"<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
"input{background:#f1f1f1;border:0;padding:0 15px}body{background:#3498db;font-family:sans-serif;font-size:14px;color:#777}"
"#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
"#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
"form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
".btn{background:#3498db;color:#fff;cursor:pointer}</style>";




/* Server Index Page */
String firmwarepage = 
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
"<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
"<label id='file-input' for='file'>   Choose file...</label>"
"<input type='submit' class=btn value='Update'>"
"<br><br>"
"<div id='prg'></div>"
"<br><div id='prgbar'><div id='bar'></div></div><br></form>"
"<script>"
"function sub(obj){"
"var fileName = obj.value.split('\\\\');"
"document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
"};"
"$('form').submit(function(e){"
"e.preventDefault();"
"var form = $('#upload_form')[0];"
"var data = new FormData(form);"
"$.ajax({"
"url: '/update',"
"type: 'POST',"
"data: data,"
"contentType: false,"
"processData:false,"
"xhr: function() {"
"var xhr = new window.XMLHttpRequest();"
"xhr.upload.addEventListener('progress', function(evt) {"
"if (evt.lengthComputable) {"
"var per = evt.loaded / evt.total;"
"$('#prg').html('progress: ' + Math.round(per*100) + '%');"
"$('#bar').css('width',Math.round(per*100) + '%');"
"}"
"}, false);"
"return xhr;"
"},"
"success:function(d, s) {"
"console.log('success!') "
"},"
"error: function (a, b, c) {"
"}"
"});"
"});"
"</script>" + style;
