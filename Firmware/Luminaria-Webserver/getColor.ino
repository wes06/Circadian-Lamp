
/* 
 -4000        100%   cold     0%  warm
     0        100%   cold   100%  warm
  4000          0%   cold   100%  warm
*/


int colorTemp = 0; 



void getColor(int awakenHour) {  // awakenHour 0 = waking up, awakenHour 16 = going to sleep

  int enterPlateau = 3;
  int leavePlateau = 13;

  if (awakenHour <= enterPlateau) {
    colorTemp = (  (enterPlateau - awakenHour)/enterPlateau  ) * -4000;
  }
  else if (awakenHour > enterPlateau || awakenHour < leavePlateau) {
    colorTemp = 0; // full light
  }
  else {
    colorTemp = (  (awakenHour - leavePlateau)/(16 - leavePlateau)  ) * 4000;
  }

}


void getBrightness(int awakenHour){
  
}
}

