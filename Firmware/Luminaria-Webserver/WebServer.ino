// http://arduino.stackexchange.com/a/13391/7734

const char * vogon_poem = R"html(
             O freddled gruntbuggly thy micturations are to me<br>
                 As plured gabbleblochits on a lurgid bee.<br>
              Groop, I implore thee my foonting turlingdromes<br>
           And hooptiously drangle me with crinkly bindlewurdles,<br>
Or I will rend thee in the gobberwarts with my blurlecruncheon, see if I don't<br>
<br><br>
                (by Prostetnic Vogon Jeltz; see p. 56/57)</ br>
)html";




void webServer(){
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) 
    {
  
        // Wait until the client sends some data
        Serial.println("new client");

        // an http request ends with a blank line
        boolean done = false;
        while (client.connected() && !done) 
          {
          while (client.available () > 0 && !done)
            done = processIncomingByte (client.read ());
          }  // end of while client connected

        // Return the response
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println(""); //  do not forget this one
        client.println(""
        "<!DOCTYPE html>"
        "<html>"
        "<body onLoad=\"myFunction()\">");
        client.println("<script>");
        client.println("function myFunction() {");
        client.println("    var x = document.createElement(\"INPUT\");");
        client.println("    x.setAttribute(\"type\", \"range\");");
        client.println("    document.body.appendChild(x);");
        
        client.println("}");
        client.println("</script>");
        client.print(vogon_poem);
        client.print("Led pin is now: ");
      
   /*     if(value == HIGH) {
          client.print("On");  
        } else {
          client.print("Off");
        }*/
      
        client.println("<br><br>");
        client.println("Click <a href=\"/WR-1000-1000-1000-1000\">here</a> turn the LED on pin 2 ON<br>");
        client.println("Click <a href=\"/WR-0-0-0-0\">here</a> turn the LED on pin 2 OFF<br>");
        client.println("</body>");
      
        client.println("</html>");
      
        // give the web browser time to receive the data
        delay(10);
        // close the connection:
        client.stop();
        Serial.println(F("Client disconnected"));
    }

}







/*
        // Read the first line of the request
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.flush();
         
        // Match the request
        int value = LOW;
        if (request.indexOf("/LED=ON") != -1) {
          swSer.print("WR-1000-1000-1000-1000\r\n");
          value = HIGH;
        } 
        if (request.indexOf("/LED=OFF") != -1){
          swSer.print("WR-0-0-0-0\r\n");
          value = LOW;
        }
      
        // Set ledPin according to the request
       // digitalWrite(ledPin, value);

       */
