Action()
{

	lr_start_transaction("02_Login");
	
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

/*Correlation comment - Do not change!  Original value='134602.71672742zQcDzcHpctVzzzzHtVftVpHzDtf' Name ='userSession' Type ='ResponseBased'*/
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

	/* FindTicket */
	
	lr_think_time(5);

	lr_start_transaction("login");

	web_websocket_close("ID=0", 
		"Code=1000", 
		LAST);

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
		"Name=login.x", "Value=51", ENDITEM,
		"Name=login.y", "Value=11", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	web_websocket_close("ID=1", 
		"Code=1000", 
		LAST);

	web_websocket_close("ID=2", 
		"Code=1000", 
		LAST);

	web_websocket_close("ID=3", 
		"Code=1000", 
		LAST);

	web_websocket_close("ID=4", 
		"Code=1000", 
		LAST);

	lr_end_transaction("login",LR_AUTO);

	web_websocket_close("ID=5", 
		"Code=1000", 
		LAST);

	web_websocket_send("ID=6", 
		"Buffer={\"subscribe\":{\"eyJjIjoibm90aWZpY2F0aW9uLWNoYW5nZWQ6MTExODQ4MDg2IiwidCI6MTY2MTY3MDUzOX0=--3960bdd12f2497b82a7737712b8df3bf5165447915690b75e58cad7ec6fdccb1\":\"\",\"eyJjIjoicmVwbzo1Mjc4NjI0MTg6cG9zdC1yZWNlaXZlOjExMTg0ODA4NiIsInQiOjE2NjE2NzA1ODN9--6568685d8a6d0ab342a52be4d4a7e894aa2f8b73634d4f42d2dd52ccd3fdcf30\":\"\"}}", 
		"IsBinary=0", 
		LAST);

	/*Connection ID 6 received buffer WebSocketReceive0*/


	lr_start_transaction("logout");

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text/IC=A Session ID has been created and loaded into a cookie called MSO",
		LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);
	
	lr_end_transaction("02_Login",LR_AUTO);

	return 0;
}