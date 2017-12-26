
/*ok! */
#define HTTP_HEAD "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";

#define HTTP_WEB_BASIC_REALM  "HTTP/1.1 401 Authorization Required\r\n Server: MP-LINK WEBSERVER V1.0 \r\n WWW-Authenticate: basic realm=\"MP-LINK V1.0 技术多交流\"\r\n\r\n  <html><body>401 error! Please check your Username and Password!</body></html>\r\n";
//<body bgcolor=\"#3030A0\" text=\"#FFFFFF\"> 

#define  INDEX_DATA__	\
"\
<html>\
<head>\
<STYLE TYPE=\"text/css\">\
body{\
font-family:\"Lucida Grande\", \"Lucida Sans Unicode\",Verdana, Arial, Helvetica, sans-serif;\
font-size:12px;\
}\
p, h1, form, button{border:0; margin:0; padding:0;}\
.spacer{clear:both; height:1px;}\
.myform{\
    margin:0 auto;\
    width:400px;\
    padding:14px;\
}\
#stylized{\
    border:solid 2px #b7ddf2;\
    background:#ebf4fb;\
}\
#stylized h1 {\
    font-size:14px;\
    font-weight:bold;\
    margin-bottom:8px;\
}\
#stylized p{\
    font-size:11px;\
    color:#666666;\
    margin-bottom:20px;\
    border-bottom:solid 1px #b7ddf2;\
    padding-bottom:10px;\
}\
#stylized label{\
    display:block;\
    font-weight:bold;\
    text-align:right;\
    width:140px;\
    float:left;\
}\
#stylized .small{\
    color:#666666;\
    display:block;\
    font-size:11px;\
    font-weight:normal;\
    text-align:right;\
    width:140px;\
}\
#stylized input{\
    float:left;\
    font-size:12px;\
    padding:4px 2px;\
    border:solid 1px #aacfe4;\
    width:200px;\
    margin:2px 0 20px 10px;\
}\
#stylized button{\
    clear:both;	\
    margin-left:150px;\
    width:125px;\
    height:31px;\
    background:#666666 url(img/button.png) no-repeat;\
    text-align:center;\
    line-height:31px;\
    color:#FFFFFF; \
    font-size:11px;\
    font-weight:bold;\
}\
</STYLE>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\
<title>A Webserver test </title></head>\
<body> \
<div id=\"stylized\" class=\"myform\">	\
<form method=\"POST\" action=\"/vReback.asp\" ENCTYPE=\"multipart/form-data\" onsubmit=\"alert( testform.fname.value )\"-onsubmit>\
	<!--webbot bot=\"SaveResults\" U-File=\"_private/form_results.csv\" S-Format=\"TEXT/CSV\" S-Label-Fields=\"TRUE\" startspan --><input TYPE=\"hidden\" NAME=\"VTI-GROUP\" VALUE=\"0\">\
	<h1>This is a small test page. Lwip 1.3.2 Cortex -M3 STM32F103VC</h1>\
	 <label>Input you name\
           <span class=\"small\">Input name</span>\
</label>\
	<input type=\"text\" name=\"yourname\">\
		<label>\
		Input you age:\
			</label>\
	<input type=\"text\" name=\"yourage\">\
	<label>\
	输入你的IP0:\
		</label>\
	<input type=\"text\" name=\"yourip\">\
	<label>Input you age:</label>\
	<input type=\"text\" name=\"yourage\">\
	<input type=\"submit\" value=\"提交\">\
	</form>\
	</div>\
	</body>\
	</html>\
";
//***************************************************************************************************************

#define INDEX_DATA 	 "\
<html>\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\
<title>A Webserver test </title>\
</head>\
</body>\
<form method=\"POST\" action=\"/vReback.asp\" ENCTYPE=\"multipart/form-data\" onsubmit=\"alert( testform.fname.value )\"-onsubmit>\
<!--webbot bot=\"SaveResults\" U-File=\"_private/form_results.csv\" S-Format=\"TEXT/CSV\" S-Label-Fields=\"TRUE\" startspan --><input TYPE=\"hidden\" NAME=\"VTI-GROUP\" VALUE=\"0\"><!--webbot bot=\"SaveResults\" i-checksum=\"43374\" endspan -->\
This is a small test page. Lwip 1.3.2 Cortex -M3 STM32F103VC\
<p>  Input you name:\
<input type=\"text\" name=\"yourname\">\
<p>  Input you age:\
<input type=\"text\" name=\"yourage\">\
<p> 输入你的IP:\
<input type=\"text\" name=\"yourip\">\
<p>  Input you age:\
<input type=\"text\" name=\"youraggggggggggg\">\
\">[刷新]</a></small></p>\n<p><a href=\"\
/0\">关闭LED</a><p>\
\">[刷新_1]</a></small></p>\n<p><a href=\"\
/1\">Hello Word!<a><p>\
</p>\
<INPUT type=file name=\"Whatever\">\
<INPUT type=submit value=\"  OK  \"></td>\
</p>\
please chose your favorate frute:\
<input type=\"checkbox\" name=\"fruit\" value =\"apple\" checked >啊喜\
<input type=\"checkbox\" name=\"fruit\" value =\"orange\"checked>啊耿\
<input type=\"checkbox\" name=\"fruit\" value =\"mango\">啊泰\
<input type=\"submit\" value=\"提交\">\
</form>\
</body> \
</html>\
"; 

#define TABLE "\
<form action=\"www.baidu.com\"  method=\"post\">\
<input type=\"text\" name=\"name3\" tabindex=\"30\" size=\"15\" maxlength=\"5\"title=\"请输入姓名\" /><br>\
<input type=\"submit\" value=\"提交\" name=\"name\">\
</form>\
";

#define TABLE2 "\
<form action=\"checkUser.html?opt=xxx\" method=\"POST\"enctype=\"multipart/form-data\">\
<input type=\"text\" name=\"username\" value=\"yyy\"/>\
<input type=\"text\" name=\"age\" value=\"zzz\"/>\
<input type=\"file\" name=\"file\"/>\
<inupt type=\"submit\" value=\"submit\"/>\
</form>\
";
/*
const static uint8 http_html_hdr[] =  "HTTP/1.0 200 OK\r\n\
	Content-type: text/html\r\n\
	\r\n\
	<html> \
	<head><title>lwIP Web</title></head> \
	<body bgcolor=\"#3030A0\" text=\"#FFFFFF\"> \
	<p><b><font color=\"#FFFF00\" size=\"6\"><i>lwIP Web</i></font></b></p> \
	<p><b>This is a website hosted by the embedded Webserver</b> <b>lwIP WEB.</b></p> \
	<p><b>Hardware:</b></p> \
	<ul> \
	<li><b>Keil MCB2300 board, 72 MHz, 512KB Flash, 96 KB SRAM</b></li> \
	<li><b>Embedded EMAC Ethernet Controller</b></li> \
	</ul> \
	</body> \
	</html>";*/
