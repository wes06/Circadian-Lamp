
int outMin = 700;//280;
//int outMax = 1500;

//long inMin = 0;
//long inMax = 1048576; //pow(1024)
double frac = 0.0023;//double(outMax - outMin) / double(inMax - inMin);
//printDouble(frac, 1000000000L); //0.00009536743164



int map2(long x)
{
  return int(double(x)*frac) + outMin;
}


void animate() {
  for(int canal=0;canal<4;canal++){
    switch(params[4]){
      case 0:
        linear(canal);
        break;
      case 1:
        inst(canal);
        break;
      case 2:
        accel(canal);
        break;
      default:
        currVal[canal] = 1023;
      break;
    }

     //long valor = sq(currVal[canal]);//*currVal[canal];
     //int newValor = map2(valor); 
    //Serial.println(currVal[canal]);
     //writeDac(channel[canal], newValor);
     writeDac(channel[canal], currVal[canal]);
  }
}

void inst(int _canal){
  currVal[_canal] = tarVal[_canal];
}

void linear(int _canal){

      if (currVal[_canal] < tarVal[_canal]) {
         currVal[_canal] += valChange;
         if (currVal[_canal] > tarVal[_canal]){
               currVal[_canal] = tarVal[_canal];
         };
      }else if(currVal[_canal] > tarVal[_canal]){
         currVal[_canal] -= valChange;
         if(currVal[_canal] < tarVal[_canal]){
              currVal[_canal] = tarVal[_canal];
         };    
      };
   }


void accel(int _canal){
  
}
