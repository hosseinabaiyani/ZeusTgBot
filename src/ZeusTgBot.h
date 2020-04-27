/*
 * ZeusTgBot.h
 *     Author: Mazarei
 *     Edited by: Hossein 2020 April 27
 */

#ifndef ZEUSTGBOT_H_
#define ZEUSTGBOT_H_
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"
#include <WiFiClientSecureBearSSL.h>
// Fingerprint for Your URL, this is Bale api fingerprint and but may be expired when you use it,so it needs to be updated well before use, but if you use insecure method you can ignore it because it's useless then.
// You can find fingerprints at this site https://www.grc.com/fingerprints.htm
const uint8_t fingerprint[20] = {0x57, 0xDE, 0xC0, 0xB0, 0x5F, 0xCB, 0x17, 0x8C, 0xA4, 0xF2, 0x31, 0xFC, 0x18, 0x38, 0x33, 0x67, 0xCC, 0x01, 0x53, 0x33};


#define TG_HOST 		"https://api.telegram.org"
#define BALE_HOST 		"https://tapi.bale.ai"
#define LIMIT_Message	1

typedef void (*Message_Event) (String Message_id,String Message_From,String Message_Text,bool is_callback,String Call_ID);

class Zeus_TgBot {
public:

	typedef struct
	{
		uint32_t	id;
		String		first_name;
		String		last_name;
		String		username;
	}User_t;

	Zeus_TgBot(String token, bool IsBale=false, bool debug=false);
	virtual ~Zeus_TgBot();

	void Set_Message_Event(Message_Event Event_Call);
	bool GetMe(User_t *User);
	bool GetUpdates();
	bool sendMessage(String chat_id, String text);
	bool sendMessage(String chat_id, String text, String reply_markup);
	bool answerCallbackQuery(String callback_query_id,String Text);
	bool EditMessage(String msg_id,String chat_id, String text, String reply_markup);

	void SetProxyHost(String pHost);
	
private:
	String botkey;

	volatile uint32_t	UpdateID;

	String SendCommand(String command, JsonObject& payload);
	void ProssessOneMessage(JsonObject& Message);
	void ProssessOneCallBack(JsonObject& Message);

	Message_Event Func_Message_Event;
	bool is_debug = false;
	String   zHost;
	bool     IsProxy;
};

#endif /* ZEUSTGBOT_H_ */
