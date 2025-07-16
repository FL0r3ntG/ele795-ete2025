/*struct inputData {
  int* flexion;
  int joyX;
  int joyY;
  bool joyClick;
  bool triggerButton;
  bool aButton;
  bool bButton;
  bool grab;
  bool pinch;
};

struct outputData{
  int* hapticLimits;
};
*/

#if ENCODING == ENCODING_LEGACY
//legacy encoding
char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  static char stringToEncode[75];
  
  sprintf(stringToEncode, "%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d&%d\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, joyClick,
  triggerButton, aButton, bButton, grab, pinch
  );
  return stringToEncode;
}
//legacy decoding
void decodeData(char* stringToDecode, int* hapticLimits){
    byte index = 0;
    char* ptr = strtok(stringToDecode, "&");  // takes a list of delimiters
    while(ptr != NULL)
    {
        hapticLimits[index] = atoi(ptr);
        index++;
        ptr = strtok(NULL, "&");  // takes a list of delimiters
    }
}
#endif

#if ENCODING == ENCODE_ALPHA
//alphabetic encoding
char* encode(int* flexion, int joyX, int joyY, bool joyClick, bool triggerButton, bool aButton, bool bButton, bool grab, bool pinch, bool calib, bool menu){
  static char stringToEncode[75];
  int trigger = (flexion[1] > ANALOG_MAX/2) ? (flexion[1] - ANALOG_MAX/2) * 2:0;
  #if USING_SPLAY
  sprintf(stringToEncode, "A%dB%dC%dD%dE%dF%dG%dP%d%s%s%s%s%s%s%s%s(AB)%d(BB)%d(CB)%d(DB)%d(EB)%d\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, trigger, joyClick?"H":"",
  triggerButton?"I":"", aButton?"J":"", bButton?"K":"", grab?"L":"", pinch?"M":"", menu?"N":"", calib?"O":"",
  flexion[5], flexion[6], flexion[7], flexion[8], flexion[9]
  );
  #else
  sprintf(stringToEncode, "A%dB%dC%dD%dE%dF%dG%dP%d%s%s%s%s%s%s%s%s\n", 
  flexion[0], flexion[1], flexion[2], flexion[3], flexion[4],
  joyX, joyY, trigger, joyClick?"H":"",
  triggerButton?"I":"", aButton?"J":"", bButton?"K":"", grab?"L":"", pinch?"M":"", menu?"N":"", calib?"O":""
  );
  #endif
  return stringToEncode;
}

//alpha decoding
void decodeData(char* stringToDecode, int* hapticLimits, int* vibrationIntensity, int* temperature){

  // Check for command-based messages
  if (strchr(stringToDecode, 'Z') != NULL) {
    bool toReturn = false;
    if (strstr(stringToDecode, "ClearData") != NULL) {
        clearFlags();
        toReturn = true;
    }
    if (strstr(stringToDecode, "SaveInter") != NULL) {
        saveIntermediate();
        toReturn = true;
    }
    if (strstr(stringToDecode, "SaveTravel") != NULL) {
        saveTravel();
        toReturn = true;
    }

    if (toReturn)
      return;
  }

  // Parse haptic limits (A-E)
  hapticLimits[0] = getArgument(stringToDecode, 'A'); // thumb
  hapticLimits[1] = getArgument(stringToDecode, 'B'); // index
  hapticLimits[2] = getArgument(stringToDecode, 'C'); // middle
  hapticLimits[3] = getArgument(stringToDecode, 'D'); // ring
  hapticLimits[4] = getArgument(stringToDecode, 'E'); // pinky

  // Parse vibration intensities (F-J)
  vibrationIntensity[0] = getArgument(stringToDecode, 'F'); // thumb
  vibrationIntensity[1] = getArgument(stringToDecode, 'G'); // index
  vibrationIntensity[2] = getArgument(stringToDecode, 'H'); // middle
  vibrationIntensity[3] = getArgument(stringToDecode, 'I'); // ring
  vibrationIntensity[4] = getArgument(stringToDecode, 'J'); // pinky

  // Parse temperature (T)
  *temperature = getArgument(stringToDecode, 'T');
}


int getArgument(char* stringToDecode, char command){
  char* start = strchr(stringToDecode, command);
  if (start == NULL)
    return -1;
  else
    return atoi(start + 1);
}

#endif
