//#ifndef SFMLFUNCTIONS_h
//#define SFMLFUNCTIONS_h
//
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//
//using namespace std;
//using namespace sf;
//
//VideoMode desktopsize = VideoMode::getDesktopMode();
//
////***********************************************************************************
////Function to Write the Text, also helpful in other functions 
////***********************************************************************************
////\param window The RenderWindow object in usage
////\param name The text to be written, must be a string
////\param mainFont The font to be used
////\param fontSize give the fontsize you would use in 1920x1080 resolution. It will adjsut to all screens
////\param horizontal x-axis of screen for the text. Enter -1 for center-align
////\param vertical y-axis of screen for the text. Enter -1 for center-align
////\param width Enter Width of button for center alignment if being used in button. Else 0
////\param height Enter Height of button for center alignment if being used in button. Else 0
////\param bold True for bold, else false
////\param color Enter Font Color
//void writeText(RenderWindow& window, string name, Font& mainFont,float fontSize, int horizontal, int vertical, int width, int height, bool bold, Color color) {
//
//    Text text;
//    text.setFont(mainFont);
//    if (bold)
//        text.setStyle(Text::Bold);
//
//    fontSize *= desktopsize.width / 1920.0;
//
//    text.setCharacterSize(fontSize);
//       
//    text.setFillColor(color);//Bluish-Black
//
//    text.setString(name);//Button name
//
//    FloatRect textRect = text.getLocalBounds(); //gets the coordinates of Text
//    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); //now origin will be placed on the given location instead of top right corner
//
//    if (horizontal == -1) {
//        horizontal = desktopsize.width;
//    }
//    if (vertical == -1) {
//        vertical = desktopsize.height;
//    }
//    text.setPosition(horizontal + width / 2.0f, vertical + height / 2.0f);//Finds centre of button and places text there
//
//    window.draw(text);
//
//}
//
////**********************************************************************************
//// Function to Make Buttons with centre Aligned text. Returns FloatRect
////**********************************************************************************
////\param window RenderWindow currently in use
////\param mainFont The Font for Button Text
////\param fontSize give the fontsize you would use in 1920x1080 resolution. It will adjsut to all screens
////\param fontColor Enter the required color of the font
////\param name The text to be written, must be a string
////\param width Enter the required width of the button
////\param height Enter the required height of the button
////\param horizontal Enter the required x-axis for the button. Enter zero for horizontal center alignment
////\param vertical Enter the required y-axis for the button
////\param buttonColor Enter the required fill color for the Button
////\param outLineColor Enter the required outline color
////\param hoverColor Enter color you want the button to change upon mouse hovering. Use same as button color for no hovering
////\param hoverText Enter color you want the text to change upon mouse hovering
//FloatRect makeButtons(RenderWindow& window, Font& mainFont, float fontSize, Color fontColor, string name, int width, int height, int horizontal, int vertical, Color buttonColor = Color::White, Color outLineColor = Color::Black, Color hoverColor = Color::White, Color hoverText = Color::Black) {
//    //gets screen size info to set button on centre
//    if (horizontal == 0) {
//        horizontal = (desktopsize.width / 2) - (width / 2);
//    }
//
//
//    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
//
//    RectangleShape button(Vector2f(width, height));
//    button.setPosition(Vector2f(horizontal, vertical));
//    button.setOutlineThickness(2);
//    button.setFillColor(buttonColor);
//    button.setOutlineColor(outLineColor);
//    if (button.getGlobalBounds().contains(mousePos)) {
//        button.setFillColor(hoverColor);
//        fontColor = hoverText;
//    }
//    window.draw(button);
//    //writing the text
//    writeText(window, name, mainFont, fontSize, horizontal, vertical, width, height, false, fontColor);
//
//    return button.getGlobalBounds();
//}
//
//#endif