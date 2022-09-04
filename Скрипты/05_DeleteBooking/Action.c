Action()
{
	
	/*Possible OAUTH authorization was detected. It is recommended to correlate the authorization parameters.*/

	lr_start_transaction("05_DeleteBooking");
	
	lr_start_transaction("open_home_page");
	
	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Chromium\";v=\"104\", \" Not A;Brand\";v=\"99\", \"Google Chrome\";v=\"104\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=A Session ID has been created and loaded into a cookie called MSO",
		LAST);

/*Correlation comment - Do not change!  Original value='134603.256622114zQcDzffpAVcftVftVpQDAAHf' Name ='userSession' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("open_home_page",LR_AUTO);

	/* DeleteBooking */

	lr_start_transaction("login");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=User password was correct",
		LAST);
	
	web_reg_find("Fail=NotFound",
		"Text=Welcome, <b>{Login}</b>",
		LAST);

	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={Login}", ENDITEM,
		"Name=password", "Value={Password}", ENDITEM,
		"Name=login.x", "Value=75", ENDITEM,
		"Name=login.y", "Value=8", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);
	
	

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("click_Itinerary");

	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(6);
	
	web_reg_find("Fail=NotFound",
		"Text=Itinerary",
		LAST);
	
	

/*Correlation comment - Do not change!  Original value='168964906-806-JB' Name ='flightID' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=flightID",
		"TagName=input",
		"Extract=value",
		"Name=flightID",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/itinerary.pl*",
		LAST);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	web_websocket_close("ID=0", 
		"Code=1000", 
		LAST);

	lr_end_transaction("click_Itinerary",LR_AUTO);

	web_websocket_close("ID=1", 
		"Code=1000", 
		LAST);
	
	lr_start_transaction("delete_booking");

	web_websocket_close("ID=2", 
		"Code=1000", 
		LAST);

	web_websocket_close("ID=3", 
		"Code=1000", 
		LAST);

	web_websocket_close("ID=4", 
		"Code=1000", 
		LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
	web_reg_find("Fail=NotFound",
		"Text=Itinerary",
		LAST);

	web_submit_form("itinerary.pl", 
		"Snapshot=t10.inf", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM,  
		LAST);

	lr_end_transaction("delete_booking",LR_AUTO);

	lr_start_transaction("logout");

	web_websocket_close("ID=5", 
		"Code=1000", 
		LAST);

	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(6);
	
	web_reg_find("Fail=NotFound",
		"Text/IC=A Session ID has been created and loaded into a cookie called MSO",
		LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	web_websocket_close("ID=6", 
		"Code=1000", 
		LAST);

	web_websocket_send("ID=7", 
		"Buffer={\"subscribe\":{\"eyJjIjoibm90aWZpY2F0aW9uLWNoYW5nZWQ6MTExODQ4MDg2IiwidCI6MTY2MTY3NzIwM30=--7de6aa146691e18308039e486f209fef9374fcf98d8be7197a89a218bfcaec7f\":\"\",\"eyJjIjoicmVwbzo1Mjc4NjI0MTg6cG9zdC1yZWNlaXZlOjExMTg0ODA4NiIsInQiOjE2NjE2NzcyNTZ9--2d4d1b7e777c03b6135b9d626f399869f54042b3e55711e7f111a65e65e57497\":\"\"}}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 7 received buffer WebSocketReceive0*/

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("05_DeleteBooking",LR_AUTO);

	return 0;
}