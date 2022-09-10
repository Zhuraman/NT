Action()
{

	//to generate a random 4 digit alphabet word
	
	
	char *sBuff1;
	char *sBuff2, *sBuff3, *sBuff4;
	
	sBuff1 = lr_eval_string("{pRandomLatter}");
	sBuff2 = lr_eval_string("{pRandomLatter}");
	sBuff3 = lr_eval_string("{pRandomLatter}");
	sBuff4 = lr_eval_string("{pRandomLatter}");
		
    lr_param_sprintf("FinalWord", "%s%s%s%s",sBuff1, sBuff2, sBuff3, sBuff4);
	
	lr_start_transaction("04_NewUsr");
	
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
		"\"Google Chrome\";v=\"105\", \"Not)A;Brand\";v=\"8\", \"Chromium\";v=\"105\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=A Session ID has been created and loaded into a cookie called MSO",
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

	lr_start_transaction("click_sign_up_now");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text=Customer Profile",
		LAST);

	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("click_sign_up_now",LR_AUTO);

	lr_start_transaction("data_usr");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Thank you, <b>{FinalWord}</b>",
		LAST);

	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={FinalWord}", ENDITEM, 
		"Name=password", "Value={FinalWord}", ENDITEM, 
		"Name=passwordConfirm", "Value={FinalWord}", ENDITEM, 
		"Name=firstName", "Value={FinalWord}", ENDITEM, 
		"Name=lastName", "Value={FinalWord}", ENDITEM, 
		"Name=address1", "Value={FinalWord}", ENDITEM, 
		"Name=address2", "Value={FinalWord}", ENDITEM, 
		"Name=register.x", "Value=63", ENDITEM, 
		"Name=register.y", "Value=11", ENDITEM, 
		LAST);

	lr_end_transaction("data_usr",LR_AUTO);

	lr_start_transaction("welcome_new_usr");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Welcome, <b>{FinalWord}</b>",
		LAST);

	web_url("button_next.gif", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("welcome_new_usr",LR_AUTO);
	
	lr_start_transaction("click_flights");

	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text/IC=Departure Date Applet",
		LAST);

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("click_flights",LR_AUTO);

	lr_start_transaction("find_ticket");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);
	
	web_reg_save_param("outboundFlight",
		"LB=outboundFlight\" value=\"",
		"RB=\"",
		LAST);
	
	web_reg_find("Fail=NotFound",
		"Text=Find Flight",
		LAST);
	
	web_reg_find("Text/IC=Flight departing from <b>{depart}</b> to <b>{arrive}</b> on <b>{departDate}</b>",
		LAST);

	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={depart}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={arrive}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=findFlights.x", "Value=53", ENDITEM, 
		"Name=findFlights.y", "Value=10", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

	lr_end_transaction("find_ticket",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("choice_ticket");
	
	web_reg_find("Fail=NotFound",
		"Text=Payment Details",
		LAST);

	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=reserveFlights.x", "Value=49", ENDITEM, 
		"Name=reserveFlights.y", "Value=10", ENDITEM, 
		LAST);

	lr_end_transaction("choice_ticket",LR_AUTO);

	lr_start_transaction("logout");

	web_revert_auto_header("Sec-Fetch-User");
	
	web_reg_find("Fail=NotFound",
		"Text/IC=A Session ID has been created and loaded into a cookie called MSO",
		LAST);

	lr_think_time(5);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("04_NewUsr",LR_AUTO);

	return 0;
}