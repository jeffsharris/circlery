#include "FastLED.h"
#include "SPI.h"

// Simple test for 160 (5 meters) of LPD8806-based RGB LED strip
// Not compatible with Trinket/Gemma due to limited RAM

/*****************************************************************************/

// Number of RGB LEDs in strand:
#define N_LEDS                      312 // Number of LEDs in the pixel strip

// Size of the square image
#define N_PIXELS                    1024 // Number of pixels in the inputted image

// The number of images
#define N_PHOTOS                    9

// The multiple used to calculate the interpolation (e.g. 0.2 = 1/0.2 = 5 interpolation steps)
#define INTERPOLATION_STEPS         4

// The multiple used to calculate the interpolation between two photos
#define TRANSITION_STEPS            1

// The number of times to cycle through each image
#define LOOPS_PER_IMAGE             1

// The speed of the sculpture
#define WAIT                        10

// The color order for this strip model
#define COLOR_ORDER                 BRG

// The brightness value to use
#define BRIGHTNESS                  100

// Output pins
#define DATA_PIN                    51
#define CLOCK_PIN                   53


// Images
const uint8_t marigold[][3] PROGMEM = {{18,255,224},{23,253,238},{22,255,252},{21,255,201},{23,255,242},{16,252,229},{22,255,242},{20,255,251},{20,253,234},{24,255,233},{53,156,70},{30,236,167},{22,255,245},{25,255,254},{25,253,209},{21,251,245},{21,255,216},{28,253,237},{23,255,228},{24,239,255},{15,245,191},{229,221,53},{216,233,97},{245,227,184},{19,226,182},{23,191,137},{58,180,58},{25,250,161},{21,232,255},{20,255,189},{26,246,255},{26,245,179},{28,229,255},{28,255,192},{138,229,30},{28,236,178},{157,244,24},{130,239,16},{19,130,152},{72,28,63},{18,125,255},{25,81,255},{17,89,253},{20,119,255},{8,154,152},{118,98,49},{144,215,26},{206,120,144},{238,125,165},{20,255,231},{228,198,166},{5,111,82},{13,199,255},{16,238,196},{7,248,185},{232,195,203},{16,223,218},{23,253,196},{25,226,152},{35,255,221},{31,253,254},{17,238,215},{25,253,232},{25,250,209},{20,142,226},{25,217,255},{11,207,166},{19,216,248},{28,255,242},{10,166,238},{30,250,236},{18,211,145},{27,241,194},{23,242,255},{235,173,166},{21,251,233},{28,244,254},{29,252,236},{24,251,231},{28,253,230},{26,255,242},{31,251,252},{30,240,253},{28,253,255},{26,252,244},{19,196,238},{22,163,240},{26,252,255},{20,179,245},{15,142,208},{14,175,198},{16,132,255},{17,79,200},{29,255,161},{20,253,170},{220,133,145},{245,68,255},{22,255,247},{21,233,229},{19,38,253},{20,178,163},{23,241,220},{30,235,255},{28,255,183},{34,248,254},{25,253,231},{11,189,163},{23,237,248},{20,181,237},{30,255,223},{25,214,229},{4,124,211},{11,135,228},{15,107,255},{13,74,255},{18,131,253},{10,135,167},{232,185,165},{28,255,202},{21,172,205},{22,175,255},{33,255,254},{3,120,195},{9,157,205},{16,145,167},{9,103,197},{16,115,215},{11,127,186},{10,119,249},{16,95,254},{12,90,181},{11,112,134},{11,130,176},{17,96,122},{18,128,180},{11,106,214},{15,67,253},{21,61,99},{17,166,84},{12,126,211},{10,124,255},{15,76,255},{14,134,246},{7,138,186},{11,140,209},{13,128,205},{23,182,214},{4,122,235},{211,150,151},{223,192,200},{5,197,208},{21,216,255},{31,227,254},{31,255,243},{27,255,218},{15,221,205},{220,141,240},{2,167,201},{238,140,152},{235,125,232},{1,164,231},{26,255,189},{30,255,160},{24,184,250},{28,252,244},{24,255,238},{27,248,255},{34,241,255},{33,198,254},{3,120,112},{24,66,108},{31,173,197},{28,255,243},{29,244,174},{15,128,89},{27,243,216},{29,253,246},{30,244,195},{26,255,251},{31,246,201},{28,245,253},{20,255,231},{39,231,118},{25,243,207},{24,253,247},{27,238,140},{28,255,179},{25,235,254},{24,226,198},{22,232,195},{27,218,198},{24,224,255},{25,253,252},{23,253,255},{25,247,254},{24,242,255},{27,220,255},{27,255,225},{23,249,255},{24,248,209},{42,46,44},{24,251,193},{26,195,111},{26,190,102},{23,179,94},{29,209,122},{25,250,239},{110,215,45},{155,11,67},{87,78,55},{13,132,224},{13,112,254},{11,95,255},{14,74,255},{22,71,254},{21,77,253},{22,110,132},{18,132,158},{124,240,17},{155,255,20},{216,123,72},{123,189,43},{116,234,25},{235,114,100},{8,175,198},{20,245,204},{19,234,202},{227,187,143},{167,248,41},{120,255,32},{34,219,100},{25,255,228},{29,239,255},{23,247,199},{21,252,231},{23,253,216},{21,255,198},{26,255,200},{26,255,255},{24,247,254},{28,219,131},{21,240,156},{15,253,224},{19,245,193},{23,255,226},{28,232,254},{27,245,255},{22,255,231},{19,252,180},{27,255,187},{24,224,160},{19,240,213},{19,249,234},{17,246,255},{21,255,253},{23,252,192},{19,191,117},{148,137,78},{127,52,58},{20,137,124},{41,74,99},{26,188,173},{20,231,255},{21,206,239},{16,229,132},{19,253,240},{23,253,245},{30,222,116},{60,153,50},{32,215,65},{24,138,92},{75,67,64},{31,211,174},{32,183,153},{23,212,254},{24,236,255},{23,255,254},{22,233,255},{26,247,253},{24,247,255},{29,177,255},{26,241,252},{24,255,187},{112,86,94},{24,205,180},{19,167,240},{25,255,255},{23,241,255},{20,255,249},{88,49,72},{14,95,112},{52,105,41},{156,255,38},{145,246,57},{13,142,161},{14,132,164},{14,140,252},{14,163,128},{12,135,111},{9,98,221},{11,75,255},{20,88,252},{5,104,149},{8,119,255},{70,14,53},{137,255,50},{63,37,82},{147,250,53},{129,83,110},{23,217,255},{28,228,192},{24,113,141},{18,255,230},{21,255,216},{22,227,198},{20,253,247},{18,255,254},{19,253,241},{25,117,167},{25,139,176},{25,138,186},{22,222,255},{18,255,202},{27,85,164},{129,255,53},{10,61,83},{132,160,51},{133,255,30},{129,255,35},{156,221,15},{132,121,69},{34,80,159},{67,99,115},{21,246,170},{24,253,208},{39,156,62},{21,255,184},{29,155,171},{23,221,115},{19,255,231},{23,253,198},{20,251,233},{14,137,152},{22,161,142},{0,63,64},{19,135,173},{21,255,251},{27,234,202},{30,77,157},{87,47,92},{26,69,227},{25,61,177},{127,80,76},{126,238,45},{33,92,193},{36,98,179},{26,212,215},{19,252,248},{30,131,207},{25,87,212},{38,130,193},{34,86,195},{34,75,122},{41,104,142},{40,77,165},{37,103,151},{132,255,33},{56,84,103},{13,120,129},{13,139,95},{12,138,223},{20,103,89},{93,47,54},{132,255,24},{13,106,113},{10,112,255},{9,101,255},{8,128,240},{6,95,255},{6,99,245},{7,97,242},{9,117,214},{14,132,104},{10,136,222},{11,108,251},{10,109,177},{9,117,234},{12,141,204},{10,152,167},{2,130,198},{11,148,211},{11,120,197},{10,120,226},{16,158,179},{139,139,44},{24,194,176},{21,168,177},{9,73,255},{13,121,187},{14,112,129},{28,55,153},{30,228,224},{32,208,255},{30,99,255},{36,189,175},{35,163,142},{25,255,213},{29,255,192},{24,230,215},{21,247,236},{24,217,199},{23,122,171},{27,194,174},{29,240,254},{30,253,254},{58,118,58},{38,195,121},{30,222,255},{27,233,254},{44,114,105},{28,203,219},{27,238,210},{29,255,224},{33,230,254},{18,229,255},{9,214,193},{243,130,183},{239,170,156},{234,174,79},{27,250,245},{28,235,225},{28,242,253},{27,244,255},{21,175,129},{27,223,171},{29,238,255},{37,232,255},{34,255,215},{24,205,191},{28,255,239},{12,107,140},{10,126,221},{10,137,240},{17,125,220},{12,139,108},{20,150,100},{18,151,118},{29,218,174},{22,160,143},{246,57,66},{28,240,188},{25,188,162},{33,255,255},{18,233,225},{25,213,255},{37,246,255},{18,195,247},{34,219,255},{120,20,151},{158,75,88},{2,109,175},{226,167,122},{24,143,139},{15,159,227},{12,130,231},{20,152,212},{11,100,244},{12,103,231},{11,103,255},{9,102,196},{12,117,197},{7,52,255},{22,180,233},{18,141,186},{38,218,126},{29,255,253},{26,255,238},{23,199,196},{58,153,50},{30,171,162},{27,129,148},{27,221,98},{27,226,255},{28,255,239},{29,231,255},{22,252,250},{19,255,251},{26,247,255},{24,252,196},{24,246,221},{24,246,249},{29,245,222},{29,236,215},{27,220,255},{23,233,255},{24,237,255},{24,255,248},{25,248,110},{23,255,189},{24,253,180},{37,130,92},{18,28,220},{64,79,132},{26,232,214},{21,124,98},{228,146,117},{229,115,254},{254,86,182},{30,241,96},{22,255,172},{24,255,154},{29,247,174},{26,240,254},{12,240,253},{31,241,255},{30,252,249},{11,184,227},{230,152,164},{17,175,166},{23,232,255},{27,255,238},{31,241,187},{28,242,255},{26,248,220},{30,246,184},{24,255,248},{23,255,210},{29,255,249},{23,235,255},{26,239,203},{22,247,242},{19,242,254},{24,253,234},{26,211,129},{24,251,250},{22,235,254},{25,224,254},{23,255,167},{17,147,137},{30,181,107},{26,237,159},{23,252,242},{23,249,196},{27,226,255},{27,245,241},{25,109,140},{25,163,81},{40,93,52},{175,155,54},{26,95,120},{113,109,49},{17,96,58},{49,76,63},{27,234,191},{26,245,211},{233,9,54},{22,179,141},{19,143,110},{248,107,126},{24,250,245},{23,232,191},{25,205,187},{4,80,162},{251,69,190},{15,95,237},{26,255,233},{17,123,128},{252,121,158},{249,90,82},{34,46,137},{5,147,81},{26,191,124},{16,138,136},{21,169,134},{28,209,254},{30,210,255},{35,238,255},{28,204,191},{27,216,240},{31,242,255},{28,253,238},{31,253,253},{26,232,205},{23,172,160},{7,102,156},{12,122,152},{253,78,104},{18,179,129},{24,253,240},{14,118,162},{24,195,197},{30,239,255},{25,240,254},{19,209,123},{222,129,112},{252,152,149},{235,122,139},{3,106,124},{21,255,186},{234,121,124},{22,207,176},{22,249,227},{25,255,226},{32,231,254},{33,230,254},{19,217,155},{18,150,85},{22,187,137},{27,227,188},{28,229,255},{26,255,219},{24,248,255},{24,247,194},{23,246,201},{21,250,229},{20,228,137},{21,248,255},{21,246,255},{18,249,190},{18,231,170},{22,216,138},{22,252,247},{24,229,255},{24,255,253},{25,244,177},{21,253,226},{26,251,243},{25,253,235},{26,245,249},{19,117,141},{2,74,127},{21,127,124},{25,246,216},{24,255,240},{31,237,255},{24,253,245},{23,245,214},{27,228,255},{22,225,253},{22,252,230},{24,246,191},{21,180,75},{159,255,74},{12,136,105},{218,147,69},{14,253,204},{17,229,255},{7,177,161},{29,212,102},{23,245,183},{20,240,179},{19,249,191},{23,232,254},{37,150,73},{40,145,70},{29,251,235},{24,236,255},{20,255,246},{1,113,65},{7,138,96},{184,211,71},{250,73,66},{240,111,82},{229,89,57},{20,235,255},{8,209,167},{14,224,144},{16,229,255},{20,255,239},{27,239,164},{19,220,127},{16,253,230},{15,237,254},{16,182,92},{14,176,98},{14,234,150},{13,229,161},{25,201,100},{13,242,187},{12,243,158},{11,170,88},{12,247,196},{18,184,87},{140,105,46},{141,255,43},{146,190,51},{147,255,37},{42,71,43},{8,218,134},{11,250,174},{5,161,144},{179,127,56},{253,147,102},{16,241,190},{252,152,82},{244,129,114},{172,85,54},{13,245,204},{15,242,181},{42,115,53},{14,252,217},{13,179,94},{15,233,143},{8,255,248},{14,251,212},{17,241,185},{15,255,236},{16,205,109},{11,252,209},{16,235,167},{20,238,174},{16,225,255},{21,234,163},{133,220,44},{34,175,83},{25,220,124},{14,241,255},{15,245,197},{18,214,108},{15,253,251},{23,226,142},{19,243,195},{252,66,61},{102,130,39},{20,255,243},{25,224,255},{21,227,254},{19,239,214},{177,161,57},{33,103,69},{28,199,151},{26,243,152},{117,244,48},{151,220,52},{46,111,55},{109,162,44},{16,241,190},{18,243,184},{22,213,142},{26,233,151},{29,225,254},{23,244,233},{29,186,100},{23,244,194},{21,182,92},{27,236,167},{20,176,84},{25,255,207},{21,252,239},{13,197,132},{17,239,194},{17,253,215},{21,243,192},{18,253,199},{17,219,130},{18,253,210},{16,252,240},{17,255,241},{18,204,115},{19,230,145},{15,253,219},{17,219,128},{14,245,184},{11,255,245},{12,251,227},{10,252,231},{13,251,240},{13,248,199},{17,190,83},{23,193,87},{30,182,63},{16,255,173},{16,251,228},{18,233,145},{15,255,218},{17,255,194},{20,255,191},{26,239,144},{30,242,139},{25,243,150},{20,255,193},{21,253,227},{19,253,241},{21,221,120},{20,214,108},{20,248,147},{17,255,184},{18,253,205},{27,180,86},{29,217,115},{49,157,55},{27,208,83},{18,249,199},{16,255,198},{22,255,255},{21,255,184},{20,241,155},{18,255,247},{22,255,202},{25,236,140},{23,255,171},{251,178,116},{13,230,207},{20,255,193},{21,250,175},{22,237,146},{21,255,236},{20,242,168},{24,253,222},{24,252,230},{21,139,132},{29,252,234},{30,255,186},{7,180,136},{207,150,125},{10,180,161},{19,241,251},{29,253,216},{24,255,251},{7,205,179},{21,239,160},{31,250,172},{49,181,80},{23,244,148},{22,252,174},{21,241,154},{19,246,154},{23,255,251},{27,234,254},{24,252,232},{27,251,255},{27,253,222},{0,34,45},{19,214,152},{18,194,101},{25,243,173},{24,255,202},{25,255,214},{28,255,216},{20,236,179},{27,253,174},{17,236,176},{228,230,177},{17,230,218},{28,252,211},{24,255,213},{22,253,255},{20,255,235},{24,251,253},{252,248,201},{6,194,173},{24,255,228},{249,226,172},{3,198,121},{49,144,60},{48,233,181},{73,41,67},{27,99,121},{25,250,237},{25,252,218},{1,142,131},{233,164,135},{248,157,222},{254,110,205},{236,197,181},{233,160,250},{242,153,220},{235,255,121},{29,255,251},{29,239,255},{31,253,238},{16,235,217},{28,214,255},{27,255,247},{21,252,228},{26,255,251},{247,204,160},{0,172,154},{4,163,198},{28,255,246},{38,241,252},{21,230,154},{34,252,211},{31,229,255},{8,187,239},{239,90,206},{20,166,136},{29,255,224},{9,219,189},{22,253,147},{22,253,185},{24,255,252},{13,193,179},{3,173,157},{196,251,64},{210,64,71},{25,209,95},{246,151,89},{23,242,255},{27,236,254},{29,235,255},{16,172,142},{28,194,105},{28,239,253},{20,240,145},{23,211,159},{25,255,210},{27,252,213},{23,255,225},{250,144,97},{237,216,157},{26,252,237},{21,241,233},{26,238,255},{9,162,157},{236,131,234},{240,135,211},{228,236,98},{230,195,164},{222,138,197},{247,211,134},{19,238,246},{23,227,229},{28,255,188},{27,229,255},{28,255,228},{29,244,255},{24,255,240},{27,189,120},{76,76,63},{35,198,86},{26,255,147},{20,202,188},{11,137,191},{15,150,208},{16,171,233},{14,181,205},{14,155,234},{15,178,216},{16,195,192},{15,178,167},{17,183,128},{25,253,184},{25,234,161},{25,253,246},{23,248,200},{27,240,173},{26,231,255},{25,241,202},{26,234,160},{26,252,243},{26,255,226},{24,236,209},{13,208,193},{187,123,101},{22,206,153},{26,236,255},{27,252,197},{23,255,219},{24,255,218},{3,148,93},{25,241,116},{21,243,149},{8,190,103},{22,255,218},{21,249,182},{23,240,136},{22,255,254},{28,250,165},{30,219,114},{25,255,213},{53,118,43},{23,255,253},{26,255,232},{49,153,53},{29,255,206},{20,200,116},{19,196,117},{186,255,65},{8,193,108},{11,221,165},{229,124,111},{26,212,162},{177,248,42},{33,255,148},{25,252,232},{23,247,170},{24,228,254},{19,255,204},{11,212,174},{216,223,72},{16,249,129},{19,255,209},{17,204,111},{172,104,44},{40,196,65},{20,227,128},{21,255,215},{19,255,210},{24,127,56},{15,240,136},{19,251,220},{19,255,211},{19,231,133},{17,237,143},{175,228,49},{24,207,101},{19,240,170},{17,255,214},{16,240,155},{18,253,223},{22,253,164},{28,217,94},{20,228,255},{24,250,187},{26,225,111},{19,244,166},{17,255,199},{18,253,217},{19,238,139},{123,233,24},{30,218,92},{20,228,144},{24,220,125}};
const uint8_t campingdog[][3] PROGMEM = {{146,26,244},{120,12,255},{36,58,230},{31,126,187},{28,244,168},{26,234,159},{23,203,123},{28,218,161},{30,122,106},{13,95,67},{27,227,169},{29,253,169},{32,87,207},{51,39,215},{121,14,255},{134,13,254},{144,15,255},{36,22,222},{127,13,228},{147,13,255},{142,14,253},{143,8,255},{31,13,219},{54,11,236},{127,15,96},{17,60,93},{20,146,89},{32,198,122},{21,236,175},{27,155,166},{25,212,210},{21,237,194},{24,253,190},{22,233,214},{15,218,218},{16,250,153},{25,255,191},{26,250,156},{19,215,248},{15,199,184},{21,206,194},{23,203,194},{27,226,71},{28,255,107},{18,255,128},{14,190,166},{22,215,204},{23,239,163},{26,229,101},{15,153,45},{20,218,155},{22,225,183},{23,238,200},{25,252,188},{21,234,123},{21,249,222},{16,230,191},{21,235,116},{25,249,141},{23,238,195},{22,223,168},{19,210,144},{23,227,112},{26,233,116},{26,238,93},{29,161,98},{35,62,155},{27,255,105},{29,115,84},{29,182,81},{54,20,172},{131,22,222},{143,44,254},{148,54,255},{152,97,245},{148,94,240},{147,82,255},{147,65,255},{25,61,133},{0,0,111},{149,94,194},{151,109,244},{151,115,217},{149,117,235},{153,133,214},{154,155,202},{154,161,201},{152,142,216},{154,143,215},{154,160,198},{154,160,196},{152,145,209},{154,128,226},{153,121,221},{152,110,229},{151,119,231},{150,117,228},{153,110,227},{154,126,219},{156,121,220},{152,146,207},{152,159,193},{150,162,191},{152,149,210},{152,153,212},{149,164,191},{150,172,192},{151,146,203},{154,134,222},{153,130,217},{152,111,228},{151,110,219},{149,93,232},{148,64,254},{148,62,245},{148,94,239},{150,96,237},{151,96,241},{148,54,255},{148,60,253},{143,39,237},{37,51,165},{25,248,123},{26,186,142},{42,29,87},{148,34,241},{146,32,229},{161,19,64},{27,136,58},{130,20,184},{142,16,211},{33,139,99},{32,115,135},{32,108,136},{146,17,237},{138,20,243},{148,66,252},{148,63,249},{150,83,230},{146,85,234},{148,91,240},{146,61,253},{146,48,255},{147,91,231},{151,111,210},{150,112,227},{152,137,217},{152,135,217},{153,149,208},{151,172,194},{148,173,192},{152,154,210},{150,162,210},{149,170,183},{146,153,171},{150,159,213},{150,137,212},{151,138,215},{148,107,221},{147,109,215},{149,105,211},{149,107,221},{149,138,224},{150,137,219},{150,160,215},{146,154,175},{150,176,199},{150,155,208},{149,159,213},{150,173,196},{150,168,195},{147,161,207},{150,135,222},{150,143,226},{151,104,232},{149,99,224},{148,83,225},{146,50,226},{153,47,233},{149,85,231},{149,83,224},{148,83,229},{151,58,237},{149,50,233},{26,8,255},{134,12,250},{26,73,181},{25,56,184},{28,74,219},{35,6,244},{59,5,230},{25,71,255},{23,107,104},{32,161,93},{17,102,115},{193,112,66},{20,185,157},{27,247,134},{18,202,83},{7,113,117},{13,143,126},{7,95,48},{26,253,147},{22,218,210},{22,167,177},{23,108,113},{38,104,56},{28,214,106},{28,215,109},{17,158,177},{20,139,157},{30,236,82},{28,229,99},{25,174,76},{21,182,172},{23,173,176},{23,212,202},{21,217,233},{25,253,139},{26,250,156},{23,250,123},{18,189,186},{16,211,219},{21,255,157},{26,232,139},{30,122,167},{29,107,161},{31,205,104},{31,211,124},{26,163,109},{27,150,115},{31,129,155},{56,9,242},{24,23,209},{116,4,255},{155,12,255},{157,14,255},{30,7,255},{9,9,255},{170,8,253},{153,21,255},{164,17,252},{148,2,255},{99,3,255},{25,88,210},{30,225,114},{15,119,66},{24,66,210},{28,81,241},{26,211,128},{30,157,139},{28,56,255},{28,3,255},{127,1,255},{164,17,252},{164,17,251},{176,21,255},{29,13,253},{28,18,254},{177,17,251},{181,11,249},{216,10,250},{29,13,254},{25,18,255},{45,14,255},{42,17,255},{29,83,254},{26,103,255},{25,123,221},{47,8,255},{38,21,255},{28,123,165},{21,221,105},{21,250,111},{16,179,146},{15,159,117},{177,249,43},{7,98,117},{9,101,143},{217,127,50},{9,245,158},{14,160,203},{13,228,164},{10,255,182},{2,234,87},{14,218,159},{27,189,113},{10,137,104},{13,159,112},{27,77,86},{20,255,124},{12,245,103},{8,249,178},{14,255,144},{18,255,197},{12,255,139},{14,255,171},{22,156,246},{25,119,242},{15,146,148},{251,106,132},{14,179,146},{18,65,62},{8,136,54},{32,103,248},{42,4,255},{42,10,255},{32,110,253},{27,98,255},{29,84,244},{42,12,253},{42,12,255},{45,16,254},{36,15,254},{0,6,252},{15,8,253},{26,8,253},{39,13,255},{47,16,255},{0,0,253},{106,2,255},{42,2,254},{35,13,255},{50,11,255},{59,5,255},{35,107,246},{29,131,218},{0,0,255},{42,2,254},{34,106,239},{31,113,231},{0,0,255},{51,5,255},{34,5,255},{170,1,255},{0,0,255},{42,2,255},{212,1,255},{42,2,255},{0,0,255},{0,0,254},{0,0,255},{51,5,255},{0,0,255},{127,1,255},{127,1,255},{36,57,255},{28,148,216},{31,136,208},{0,0,255},{63,2,255},{30,128,233},{13,255,38},{6,137,126},{17,187,155},{18,244,47},{15,255,41},{20,207,91},{8,172,133},{15,171,153},{16,244,195},{18,226,236},{30,111,255},{30,155,251},{27,174,209},{18,253,174},{14,244,170},{28,161,227},{29,151,233},{30,135,254},{18,223,184},{12,216,161},{5,133,128},{8,244,48},{18,247,68},{18,194,152},{12,174,158},{13,255,52},{13,251,84},{8,162,154},{15,211,157},{15,226,160},{22,148,218},{24,147,231},{45,31,255},{40,24,255},{28,56,254},{30,50,246},{42,11,221},{152,21,221},{170,11,222},{38,25,229},{34,37,239},{42,2,219},{53,17,225},{30,48,250},{30,35,255},{27,47,255},{42,33,255},{42,33,255},{41,34,255},{36,40,253},{33,42,255},{42,34,255},{42,39,255},{40,47,255},{29,47,255},{32,42,255},{27,44,255},{28,43,255},{22,50,255},{28,49,252},{34,36,244},{27,46,255},{31,56,254},{46,23,231},{178,6,212},{154,56,214},{154,38,208},{60,8,213},{48,16,221},{20,21,228},{172,19,214},{159,19,208},{161,45,203},{176,16,196},{171,43,198},{164,73,205},{162,82,201},{156,73,214},{156,88,216},{162,99,203},{157,114,207},{153,124,205},{154,109,217},{155,95,214},{154,65,214},{156,15,210},{158,29,213},{155,77,220},{154,90,225},{158,47,222},{151,63,225},{154,103,230},{154,119,215},{153,119,216},{154,130,204},{154,140,198},{154,144,197},{152,127,214},{152,135,218},{154,148,208},{153,151,206},{152,149,198},{151,132,211},{152,135,216},{152,112,224},{151,121,219},{153,78,214},{150,80,223},{145,65,215},{148,88,202},{153,80,206},{149,61,218},{152,35,228},{147,41,221},{0,0,205},{60,8,219},{34,35,232},{42,34,254},{40,26,255},{31,34,232},{34,29,230},{29,77,252},{25,109,237},{34,28,242},{150,17,217},{135,6,205},{153,56,222},{152,61,228},{149,61,219},{150,80,222},{151,39,218},{148,22,207},{40,20,232},{24,81,235},{25,41,253},{31,17,218},{36,17,222},{26,40,255},{25,41,254},{42,13,225},{152,45,221},{151,50,227},{149,81,226},{149,81,225},{150,102,223},{150,129,212},{149,116,200},{151,105,225},{150,95,221},{151,88,213},{152,125,214},{153,118,217},{151,154,211},{152,139,216},{152,160,204},{151,155,195},{151,159,197},{149,151,205},{150,158,217},{151,169,199},{150,157,177},{147,180,191},{148,168,183},{147,139,175},{155,157,188},{153,162,190},{152,173,181},{153,176,182},{155,178,187},{154,173,182},{156,126,185},{154,183,188},{157,181,157},{157,163,148},{174,103,91},{178,149,80},{156,209,169},{154,136,150},{170,25,118},{153,210,150},{154,218,138},{157,217,109},{157,129,118},{161,52,121},{10,155,41},{247,52,77},{6,67,49},{5,107,57},{188,17,104},{19,139,119},{144,49,185},{152,75,185},{156,210,68},{158,255,25},{170,255,8},{163,109,79},{224,41,68},{236,99,54},{11,197,75},{161,255,5},{219,66,46},{10,131,70},{225,66,61},{177,150,39},{173,160,35},{170,161,41},{184,127,46},{173,68,82},{153,102,105},{154,131,140},{153,124,143},{170,122,54},{163,117,74},{156,114,143},{154,146,190},{156,122,141},{155,168,186},{154,172,185},{152,165,196},{153,158,191},{155,155,194},{152,146,204},{147,72,196},{154,127,198},{156,146,198},{157,154,191},{157,120,178},{181,15,181},{24,48,158},{161,64,119},{19,51,187},{7,17,172},{159,150,171},{170,53,161},{162,153,158},{160,128,167},{162,119,180},{158,150,176},{156,124,188},{159,122,194},{161,112,195},{164,114,181},{166,98,178},{164,91,189},{165,75,188},{168,68,197},{167,66,176},{169,82,177},{170,88,168},{172,76,176},{176,82,151},{175,82,157},{167,99,171},{169,102,170},{164,114,169},{167,114,163},{172,106,137},{215,76,57},{225,92,36},{199,76,87},{237,85,78},{224,82,65},{215,81,44},{209,109,35},{176,113,47},{204,98,44},{179,114,49},{177,68,41},{228,65,62},{199,81,50},{228,69,59},{211,100,76},{201,75,91},{195,90,65},{220,52,77},{188,116,35},{175,124,90},{167,141,157},{173,93,152},{167,90,130},{15,114,147},{0,47,128},{182,40,89},{11,131,89},{16,151,103},{20,136,206},{15,109,138},{19,137,139},{253,88,121},{197,106,55},{203,115,42},{213,98,75},{217,74,62},{219,60,51},{210,79,58},{199,80,51},{196,94,35},{172,86,47},{182,96,37},{175,70,29},{208,68,71},{212,51,59},{203,70,69},{217,72,98},{210,78,65},{221,71,64},{217,85,54},{220,95,56},{224,63,44},{184,145,42},{231,113,54},{224,105,51},{202,86,50},{215,88,49},{228,86,47},{215,81,44},{177,85,33},{217,70,65},{159,85,36},{182,93,38},{190,103,47},{176,102,35},{199,102,40},{188,108,33},{203,99,36},{222,85,39},{175,81,25},{196,97,34},{182,93,38},{208,77,36},{200,82,34},{184,63,36},{176,87,38},{176,93,38},{196,89,37},{182,96,37},{209,100,38},{203,93,38},{206,85,42},{224,80,35},{216,70,36},{192,98,44},{176,72,46},{181,70,40},{208,71,39},{219,66,46},{222,72,46},{206,96,37},{176,87,38},{200,70,40},{200,73,38},{159,74,41},{209,91,42},{196,87,38},{216,63,40},{186,104,44},{167,124,39},{182,149,53},{179,105,53},{186,102,45},{192,81,47},{196,70,47},{202,90,48},{200,66,42},{170,82,37},{176,87,38},{180,117,37},{188,85,42},{225,72,46},{196,85,39},{250,78,65},{236,106,67},{3,117,115},{9,130,111},{0,106,72},{9,90,90},{2,70,115},{9,112,118},{231,90,76},{9,72,130},{246,58,83},{252,73,69},{203,108,33},{215,75,47},{224,90,59},{195,71,71},{172,120,78},{179,83,70},{177,92,99},{235,64,79},{173,74,82},{166,184,72},{168,161,79},{164,160,102},{164,196,92},{165,183,86},{165,204,70},{173,162,80},{165,148,67},{165,238,60},{162,236,54},{166,201,48},{176,127,54},{170,122,54},{220,62,65},{204,74,58},{199,78,52},{193,102,55},{180,83,52},{188,102,52},{167,100,48},{202,81,53},{186,93,57},{174,142,52},{167,208,49},{166,197,49},{171,211,41},{173,156,39},{170,162,44},{164,195,43},{164,214,44},{167,197,53},{162,226,53},{165,223,48},{162,249,49},{164,236,55},{167,209,50},{160,232,46},{160,237,43},{161,217,41},{170,178,40},{163,211,41},{164,200,42},{171,183,43},{170,166,43},{170,184,47},{168,179,44},{170,183,39},{174,176,42},{170,166,43},{168,175,45},{174,153,45},{171,164,48},{170,142,43},{179,168,47},{176,185,44},{174,179,44},{174,175,45},{172,188,50},{169,204,56},{167,207,54},{170,186,52},{168,170,48},{163,189,47},{166,223,56},{165,201,57},{165,225,61},{165,241,57},{160,255,65},{161,255,56},{161,255,66},{168,211,64},{165,213,67},{161,255,74},{161,255,76},{161,233,83},{164,234,74},{161,225,70},{164,217,62},{167,196,52},{160,236,56},{161,242,63},{161,235,67},{160,232,57},{163,219,64},{158,222,70},{161,200,79},{163,231,76},{162,211,87},{164,207,91},{157,237,100},{157,238,106},{156,240,104},{158,255,95},{157,255,86},{157,251,75},{156,255,95},{157,252,100},{162,204,100},{162,223,80},{253,191,52},{193,130,43},{162,195,77},{157,217,128},{157,205,124},{159,211,128},{225,156,44},{3,212,54},{221,91,78},{192,78,85},{151,187,178},{154,180,184},{151,189,184},{153,189,167},{150,209,173},{152,193,179},{152,184,166},{149,188,164},{147,159,120},{208,59,81},{3,210,80},{235,153,65},{164,181,80},{152,240,127},{154,216,140},{150,209,146},{152,183,156},{152,183,163},{153,188,176},{154,208,152},{154,205,156},{149,194,174},{150,189,171},{152,207,157},{153,203,139},{152,202,141},{151,229,122},{153,204,122},{159,245,107},{157,238,93},{159,249,93},{157,255,113},{157,255,102},{187,182,35},{157,252,85},{160,255,84},{150,233,84},{156,255,83},{160,255,77},{152,205,78},{145,154,76},{137,170,91},{146,196,91},{150,221,76},{159,255,76},{159,255,79},{159,255,79},{159,255,78},{162,248,79},{161,251,77},{157,255,84},{159,252,85},{157,252,101},{156,255,100},{159,253,132},{157,224,127},{145,150,105},{159,244,98},{160,248,84},{152,159,101},{152,166,121},{152,200,126},{157,220,153},{155,232,149},{154,207,160},{150,192,176},{151,196,183},{153,221,168},{153,215,173},{152,191,182},{153,180,177},{153,212,172},{154,222,159},{155,212,151},{159,238,140},{159,231,143},{158,229,150},{158,216,154},{155,213,160},{156,217,165},{154,206,169},{155,173,179},{155,170,181},{156,194,169},{156,193,173},{155,172,186},{156,171,190},{156,193,182},{158,199,165},{156,211,166},{159,213,158},{157,213,158},{159,226,153},{159,245,140},{158,251,132},{159,236,148},{158,238,140},{159,247,136},{159,252,117},{159,255,128},{159,255,106},{159,252,95},{159,255,83},{159,255,88},{158,255,96},{157,255,112},{159,252,122},{158,247,105},{160,249,95},{160,255,87},{161,255,83},{164,240,86},{164,245,79},{165,228,68},{166,228,67},{164,251,80},{166,240,70},{162,224,59},{161,242,60},{165,232,67},{165,244,74},{163,255,80},{159,255,83},{162,255,81},{163,251,78},{165,255,70},{162,251,65},{161,255,74},{159,255,67},{163,243,66},{162,251,65},{164,255,64},{165,234,61},{163,241,57},{171,192,53},{167,222,55},{165,241,57},{165,245,56},{162,246,61},{161,242,60},{168,203,54},{177,201,43},{176,173,47},{165,210,52},{171,192,53},{166,160,43},{184,143,41},{173,136,41},{222,80,41},{170,174,38},{197,94,46},{243,102,82},{245,104,98},{245,105,80},{240,80,86},{240,83,101},{234,78,101},{222,80,92},{191,110,67},{197,79,74},{170,198,36},{167,205,57},{161,242,59},{170,213,43},{167,221,53},{164,225,60},{166,216,60},{162,223,57},{171,223,48},{179,161,49},{233,85,92},{222,90,82}};

//const uint8_t *(photos[N_PHOTOS][3]) = {*palmtrees, *lotusflower, *balloon, *planesunset, *rainbowalice, *rainbowflower, *chihuly, *ferriswheel, *cow};

// Create the array of LEDs
CRGB leds[N_LEDS];


void setup() {
  Serial.begin(9600); 
  FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, N_LEDS).setCorrection( TypicalLEDStrip ).setTemperature( HighNoonSun );
  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
  uint16_t pixelCount;
  for (pixelCount = 0; pixelCount < 312; pixelCount++) {
    leds[pixelCount] = CRGB(255, 0, 0);
  }
      FastLED.show();      
    FastLED.delay(10000); 
   for (pixelCount = 0; pixelCount < 312; pixelCount++) {
    leds[pixelCount] = CRGB(0, 255, 0);
  }
      FastLED.show();      
    FastLED.delay(10000);  
  for (pixelCount = 0; pixelCount < 312; pixelCount++) {
    leds[pixelCount] = CRGB(0, 0, 255);
  }
      FastLED.show();      
    FastLED.delay(10000); 
  
  pixelIterator(campingdog);
//  pixelIterator(lotusflower);
//  Serial.println("Palm trees");
//  transitionPhotos(lotusflower, palmtrees);
//  pixelIterator(palmtrees);
//  Serial.println("Balloon");
//  transitionPhotos(palmtrees, balloon);
//  pixelIterator(balloon);
//    Serial.println("Plane sunset");
//  transitionPhotos(balloon, planesunset);
//  pixelIterator(planesunset);
//    Serial.println("Rainbow alice");
//  transitionPhotos(planesunset, rainbowalice);
//  pixelIterator(rainbowalice);
//    Serial.println("Rainbow flower");
//  transitionPhotos(rainbowalice, rainbowflower);
//  pixelIterator(rainbowflower);
//    Serial.println("Chihuly");
//  transitionPhotos(rainbowflower, chihuly);
//  pixelIterator(chihuly);
//    Serial.println("Ferris wheel");
//  transitionPhotos(chihuly, ferriswheel);
//  pixelIterator(ferriswheel);
//    Serial.println("Cow");
//  transitionPhotos(ferriswheel, cow);
//  pixelIterator(cow);
//    Serial.println("Lotus flower");
//  transitionPhotos(cow, lotusflower);
}

void transitionPhotos(uint8_t currentImage[][3], uint8_t nextImage[][3]) {
  uint16_t currentStep;
  uint16_t pixelOffset;

  for (currentStep = 0; currentStep < 255; currentStep += 255 / TRANSITION_STEPS) {
    for(pixelOffset = 0; pixelOffset < N_LEDS; pixelOffset++) {

      CHSV color = CHSV(pgm_read_byte(&(currentImage[pixelOffset][0])),
                   pgm_read_byte(&(currentImage[pixelOffset][1])),
                   pgm_read_byte(&(currentImage[pixelOffset][2])));
      CHSV color_prime = CHSV(pgm_read_byte(&(nextImage[pixelOffset][0])),
                         pgm_read_byte(&(nextImage[pixelOffset][1])),
                         pgm_read_byte(&(nextImage[pixelOffset][2])));
      leds[pixelOffset] = blend(color, color_prime, currentStep);
    }
    FastLED.show();      
    FastLED.delay(WAIT);   
  }
}

void pixelIterator(uint8_t currentImage[][3]) {
  for (uint8_t loopCount=0; loopCount < LOOPS_PER_IMAGE; loopCount++) {
    uint16_t startingLocation;
    uint16_t pixelOffset;
    uint16_t currentStep;

    for (startingLocation = 0; startingLocation < N_PIXELS; startingLocation++) {
          Serial.println(startingLocation);
      for (currentStep = 0; currentStep < 255; currentStep += 255 / INTERPOLATION_STEPS) {
        for (pixelOffset = 0; pixelOffset < N_LEDS; pixelOffset++) {
          CHSV color = CHSV(pgm_read_byte(&(currentImage[(startingLocation+pixelOffset) % N_PIXELS][0])),
                       pgm_read_byte(&(currentImage[(startingLocation+pixelOffset) % N_PIXELS][1])),
                       pgm_read_byte(&(currentImage[(startingLocation+pixelOffset) % N_PIXELS][2])));
          CHSV color_prime = CHSV(pgm_read_byte(&(currentImage[(startingLocation+pixelOffset+1) % N_PIXELS][0])),
                             pgm_read_byte(&(currentImage[(startingLocation+pixelOffset+1) % N_PIXELS][1])),
                             pgm_read_byte(&(currentImage[(startingLocation+pixelOffset+1) % N_PIXELS][2])));

          leds[pixelOffset] = blend(color, color_prime, currentStep);
        }
        FastLED.show();      
        FastLED.delay(WAIT); 
      }
    }    
  }
}
