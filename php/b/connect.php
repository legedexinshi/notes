<?php
$host="127.0.0.1";
$db_user="root";
$db_pass="123";
$db_name="demo";
$timezone="Asia/Shanghai";

$link=mysql_connect($host,$db_user,$db_pass);
mysql_select_db($db_name,$link);
mysql_query("SET names UTF8");
?>
