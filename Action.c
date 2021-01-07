Action()
{

	int i;
	int j;
	int x;
	int resultcompare;
	int NumForDelete;
	char* s;
	char* y;
	char* mas[3];
	char* basesity;
	
	web_reg_find("Text=flightID",
		"SaveCount=Count",	             
		LAST);
	
	web_reg_find("Text=leaves",
		"SaveCount=CountLeaves",	             
		LAST);
	
	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	
		s = lr_eval_string("{Count}");
		i = atoi(s);
		lr_output_message("Number of Tickets on Page in GetAnswer: %s",lr_eval_string("{Count}"));
		lr_output_message("");
		
		y = lr_eval_string("{CountLeaves}");
		x = atoi(y);
			
		if (i == 3) {
			
			web_reg_save_param_ex(
			"ParamName=flightID1",
			"LB=flightID\" value=\"",
			"RB=\"",
			"Ordinal=1",
			SEARCH_FILTERS,
			LAST);
			
			web_reg_save_param_ex(
			"ParamName=flightID2",
			"LB=flightID\" value=\"",
			"RB=\"",
			"Ordinal=2",
			SEARCH_FILTERS,
			LAST);
			
			web_reg_save_param_ex(
			"ParamName=flightID3",
			"LB=flightID\" value=\"",
			"RB=\"",
			"Ordinal=3",
			SEARCH_FILTERS,
			LAST);
			
			if ( x == 3) {
				
				lr_output_message("Ticket only in one direction without -return ticket-");
			
				web_reg_save_param_ex(
				"ParamName=CityLeaves1",
				"LB=leaves ",
				"RB=  for",
				"Ordinal=1",
				SEARCH_FILTERS,
				LAST);
			
				web_reg_save_param_ex(
				"ParamName=CityLeaves2",
				"LB=leaves ",
				"RB=  for",
				"Ordinal=2",
				SEARCH_FILTERS,
				LAST);
			
				web_reg_save_param_ex(
				"ParamName=CityLeaves3",
				"LB=leaves ",
				"RB=  for",
				"Ordinal=3",
				SEARCH_FILTERS,
				LAST);
				
			}
			
			if ( x == 6) {
				
				lr_output_message("Ticket with return, you need see only the first DEPARURE CYTI");
			
				web_reg_save_param_ex(
				"ParamName=CityLeaves1",
				"LB=leaves ",
				"RB=  for",
				"Ordinal=1",
				SEARCH_FILTERS,
				LAST);
			
				web_reg_save_param_ex(
				"ParamName=CityLeaves2",
				"LB=leaves ",
				"RB=  for",
				"Ordinal=3",
				SEARCH_FILTERS,
				LAST);
			
				web_reg_save_param_ex(
				"ParamName=CityLeaves3",
				"LB=leaves ",
				"RB=  for",
				"Ordinal=5",
				SEARCH_FILTERS,
				LAST);
				
			}

			web_url("welcome.pl", 
			"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
			"TargetFrame=", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
			"Snapshot=t4.inf", 
			"Mode=HTML", 
			LAST);
			
			basesity = lr_eval_string("London");
			
			mas[0] = lr_eval_string("{CityLeaves1}");
			mas[1] = lr_eval_string("{CityLeaves2}");
			mas[2] = lr_eval_string("{CityLeaves3}");
			
			for (j=0; j<3; j++) {
				
				resultcompare = strcmp(basesity, mas[j]);
				
				if (resultcompare != 0) {
				
					NumForDelete = (j+1);
					
				}
				
			}
			
			lr_output_message("Number of flightID1: %s",lr_eval_string("{flightID1}"));
			lr_output_message("Leaves city-¹1 is: %s",lr_eval_string("{CityLeaves1}"));
			lr_output_message("Number of flightID2: %s",lr_eval_string("{flightID2}"));
			lr_output_message("Leaves city-¹2 is: %s",lr_eval_string("{CityLeaves2}"));
			lr_output_message("Number of flightID3: %s",lr_eval_string("{flightID3}"));
			lr_output_message("Leaves city-¹3 is: %s",lr_eval_string("{CityLeaves3}"));
			lr_output_message("");
			lr_save_int(NumForDelete, "NumberForDelete");
			lr_output_message("Number of city DELETE: %s",lr_eval_string("{NumberForDelete}"));
			
			web_submit_data("itinerary.pl", 
			"Action=http://localhost:1080/cgi-bin/itinerary.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
			"Snapshot=t5.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=flightID", "Value={flightID1}", ENDITEM, 
			"Name=flightID", "Value={flightID2}", ENDITEM, 
			"Name={NumberForDelete}", "Value=on", ENDITEM, 
			"Name=flightID", "Value={flightID3}", ENDITEM, 
			"Name=.cgifields", "Value=1", ENDITEM, 
			"Name=.cgifields", "Value=3", ENDITEM, 
			"Name=.cgifields", "Value=2", ENDITEM, 
			"Name=removeFlights.x", "Value=39", ENDITEM, 
			"Name=removeFlights.y", "Value=14", ENDITEM, 
			LAST);
			
		} else {
		
			lr_output_message("Number of Tickets don't equals 3, You need to add ticket");
		}

	return 0;
}