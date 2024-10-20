#include <M5EPD.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>  // Include ArduinoJson library for parsing JSON
#include <SD.h>
#include "prompt.h"

M5EPD_Canvas canvas(&M5.EPD);

// Variables to store credentials loaded from the SD card
String ssid = "";
String password = "";
String apiKey = "";

// Groq API endpoint
const char* apiEndpoint = "https://api.groq.com/openai/v1/chat/completions";

// User-selected options
int selectedOption = 0;
int selectedValue = 0;

// Variables to store selected values
int selectedWritingStyle = 0;
int selectedMainCharacter = 0;
int selectedCharacterDescription = 0;
int selectedAdventureTheme = 0;
int selectedGoalOrChallenge = 0;
int selectedAdditionalElement = 0;
int selectedTypeOfEnding = 0;

int headerSize = 4;
int textSize = 3;

// Variables for the story
String paragraphs[20];  // Maximum of 20 paragraphs
int paragraphCount = 0;
int currentPage = 0;

// Define the app state
enum AppState { SELECTION_MODE, READING_MODE };
AppState appState = SELECTION_MODE;

// Function to read the configuration file from SD card
void readConfig() {
  File configFile = SD.open("/config.txt");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return;
  }

  while (configFile.available()) {
    String line = configFile.readStringUntil('\n');
    line.trim();  // Remove any extra spaces or newlines

    if (line.startsWith("SSID=")) {
      ssid = line.substring(5);  // Extract the value after "SSID="
    } else if (line.startsWith("PASSWORD=")) {
      password = line.substring(9);  // Extract the value after "PASSWORD="
    } else if (line.startsWith("API_KEY=")) {
      apiKey = line.substring(8);  // Extract the value after "API_KEY="
    }
  }

  configFile.close();
  Serial.println("Config loaded:");
  Serial.println("SSID: " + ssid);
  Serial.println("Password: " + password);
  Serial.println("API Key: " + apiKey);
}

// Function to connect to Wi-Fi
void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi... ");
  WiFi.begin(ssid.c_str(), password.c_str());

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to draw the current selection screen
void drawSelectionScreen() {
  canvas.fillCanvas(0xFFFF);  // White background
  canvas.setTextColor(0x0000); // Black text
  canvas.setTextSize(headerSize);
  canvas.setCursor(10, 50);

  switch (selectedOption) {
    case 0:
      canvas.printf("Select Writing Style:\n\n");
      canvas.setTextSize(textSize);
      for (int i = 0; i < 5; i++) {
        if (i == selectedValue) {
          canvas.printf("-> %s\n", writingStyles[i]);
        } else {
          canvas.printf("   %s\n", writingStyles[i]);
        }
      }
      break;
    case 1:
      canvas.printf("Select Main Character:\n\n");
      canvas.setTextSize(textSize);
      for (int i = 0; i < 5; i++) {
        if (i == selectedValue) {
          canvas.printf("-> %s\n", mainCharacters[i]);
        } else {
          canvas.printf("   %s\n", mainCharacters[i]);
        }
      }
      break;
    case 2:
      canvas.printf("Select Character Description:\n\n");
      canvas.setTextSize(textSize);
      for (int i = 0; i < 5; i++) {
        if (i == selectedValue) {
          canvas.printf("-> %s\n", characterDescriptions[i]);
        } else {
          canvas.printf("   %s\n", characterDescriptions[i]);
        }
      }
      break;
    case 3:
      canvas.printf("Select Adventure Theme:\n\n");
      canvas.setTextSize(textSize);
      for (int i = 0; i < 5; i++) {
        if (i == selectedValue) {
          canvas.printf("-> %s\n", adventureThemes[i]);
        } else {
          canvas.printf("   %s\n", adventureThemes[i]);
        }
      }
      break;
    case 4:
      canvas.printf("Select Goal or Challenge:\n\n");
      canvas.setTextSize(textSize);
      for (int i = 0; i < 5; i++) {
        if (i == selectedValue) {
          canvas.printf("-> %s\n", goalsOrChallenges[i]);
        } else {
          canvas.printf("   %s\n", goalsOrChallenges[i]);
        }
      }
      break;
    case 5:
      canvas.printf("Select Additional Element:\n\n");
      canvas.setTextSize(textSize);
      for (int i = 0; i < 5; i++) {
        if (i == selectedValue) {
          canvas.printf("-> %s\n", additionalElements[i]);
        } else {
          canvas.printf("   %s\n", additionalElements[i]);
        }
      }
      break;
    case 6:
      canvas.printf("Select Type of Ending:\n\n");
      canvas.setTextSize(textSize);
      for (int i = 0; i < 5; i++) {
        if (i == selectedValue) {
          canvas.printf("-> %s\n", typesOfEnding[i]);
        } else {
          canvas.printf("   %s\n", typesOfEnding[i]);
        }
      }
      break;
  }

  canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
}

// Function to handle button input
void handleButtonInput() {
  M5.update();

  if (appState == SELECTION_MODE) {
    // Handle input for selection mode
    if (M5.BtnL.wasPressed()) {
      selectedValue = (selectedValue - 1 + 5) % 5;
      drawSelectionScreen();
    } else if (M5.BtnR.wasPressed()) {
      selectedValue = (selectedValue + 1) % 5;
      drawSelectionScreen();
    } else if (M5.BtnP.wasPressed()) {
      // Save the selected value
      switch (selectedOption) {
        case 0:
          selectedWritingStyle = selectedValue;
          break;
        case 1:
          selectedMainCharacter = selectedValue;
          break;
        case 2:
          selectedCharacterDescription = selectedValue;
          break;
        case 3:
          selectedAdventureTheme = selectedValue;
          break;
        case 4:
          selectedGoalOrChallenge = selectedValue;
          break;
        case 5:
          selectedAdditionalElement = selectedValue;
          break;
        case 6:
          selectedTypeOfEnding = selectedValue;
          break;
      }

      selectedOption++;
      selectedValue = 0;
      if (selectedOption > 6) {
        // Construct the complete prompt after the last selection
        String completePrompt = "Write a short story for kids that is " + String(writingStyles[selectedWritingStyle]) + ". The story should be about " + String(mainCharacters[selectedMainCharacter]) + ", who is " + String(characterDescriptions[selectedCharacterDescription]) + ". The main character goes on an adventure involving " + String(adventureThemes[selectedAdventureTheme]) + ", where they " + String(goalsOrChallenges[selectedGoalOrChallenge]) + ". The story should include " + String(additionalElements[selectedAdditionalElement]) + " to make it more interesting. The story should have a positive message, be entertaining, and end with a " + String(typesOfEnding[selectedTypeOfEnding]) + " tone.";
        Serial.println(completePrompt);

        // Send the prompt to Groq API
        sendGroqAPIRequest(completePrompt);

        // Change app state to READING_MODE
        appState = READING_MODE;
      } else {
        drawSelectionScreen();
      }
    }
  } else if (appState == READING_MODE) {
    // Handle input for reading mode
    if (M5.BtnL.wasPressed()) {
      if (currentPage > 0) {
        currentPage--;
        displayCurrentPage();
      }
    } else if (M5.BtnR.wasPressed()) {
      if (currentPage < paragraphCount - 1) {
        currentPage++;
        displayCurrentPage();
      }
    } else if (M5.BtnP.wasPressed()) {
      // Return to selection mode
      appState = SELECTION_MODE;
      selectedOption = 0;
      selectedValue = 0;
      drawSelectionScreen();
    }
  }
}

// Function to parse the story into paragraphs
void parseStoryIntoParagraphs(const char* story) {
  String storyStr = String(story);
  paragraphCount = 0;

  // Split by double newline "\n\n"
  int pos = 0;
  while (pos >= 0 && paragraphCount < 20) {
    int nextPos = storyStr.indexOf("\n\n", pos);
    if (nextPos == -1) {
      // Last paragraph
      paragraphs[paragraphCount++] = storyStr.substring(pos);
      break;
    } else {
      paragraphs[paragraphCount++] = storyStr.substring(pos, nextPos);
      pos = nextPos + 2;  // Move past the "\n\n"
    }
  }
}

// Function to display the current page
void displayCurrentPage() {
  canvas.fillCanvas(0xFFFF);  // White background
  canvas.setTextColor(0x0000); // Black text
  canvas.setTextSize(3);  // Font size for page number
  canvas.setCursor(10, 10);
  canvas.printf("Page %d/%d\n\n", currentPage + 1, paragraphCount);

  canvas.setTextSize(4);  // Larger font size for text
  canvas.setCursor(10, 70);
  canvas.print(paragraphs[currentPage]);

  canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
}

// Function to send a POST request to Groq API and display the response
void sendGroqAPIRequest(const String& userPrompt) {
  if (WiFi.status() == WL_CONNECTED) {  // Ensure Wi-Fi is connected
    HTTPClient http;

    // Start the HTTP request
    http.begin(apiEndpoint);

    // Set the headers
    http.addHeader("Authorization", String("Bearer ") + apiKey);
    http.addHeader("Content-Type", "application/json");

    // Create the JSON payload (Prompt)
    StaticJsonDocument<500> doc;
    doc["model"] = "llama3-8b-8192";
    JsonArray messages = doc.createNestedArray("messages");
    JsonObject message1 = messages.createNestedObject();
    message1["role"] = "user";
    message1["content"] = userPrompt;

    // Convert the JSON document to a string
    String requestBody;
    serializeJson(doc, requestBody);

    // Send the POST request
    int httpResponseCode = http.POST(requestBody);

    // Check the response
    if (httpResponseCode > 0) {
      String response = http.getString();  // Get the response as a string

      // Parse the JSON response
      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 5000;
      DynamicJsonDocument responseDoc(capacity);
      DeserializationError error = deserializeJson(responseDoc, response);
      if (error) {
        Serial.print("Error parsing JSON: ");
        Serial.println(error.c_str());
        return;
      }

      // Extract the answer from the response
      const char* answer = responseDoc["choices"][0]["message"]["content"];
      Serial.println("Answer from API:");
      Serial.println(answer);

      // Parse the story into paragraphs
      parseStoryIntoParagraphs(answer);

      // Reset current page
      currentPage = 0;

      // Display the first page
      displayCurrentPage();

    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Close the connection
  } else {
    Serial.println("Wi-Fi not connected");
  }
}

void setup() {
  // Start M5Paper and Serial
  M5.begin();
  Serial.begin(115200);

  // Initialize SD card
  if (!SD.begin()) {
    Serial.println("SD card initialization failed!");
    return;
  }

  // Load the credentials from the config.txt file
  readConfig();  // Load credentials from config.txt file

  // Display the image from the SD card
  canvas.createCanvas(960, 540);
  canvas.fillCanvas(0xFFFF);  // White background
  canvas.setTextColor(0x0000); // Black text
  if (SD.exists("/logo.jpg")) {
    canvas.drawJpgFile(SD, "/logo.jpg", 0, 0);
    Serial.println("Image displayed successfully!");
  } else {
    Serial.println("logo.jpg not found on SD card!");
  }
  canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);

  // Connect to Wi-Fi
  connectToWiFi();

  // Draw initial menu
  drawSelectionScreen();
}

void loop() {
  // Handle button input
  handleButtonInput();
}