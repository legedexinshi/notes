<?php

$con = mysql_connect('127.0.0.1','root','123');
mysql_select_db("test", $con);
$sql = "SELECT day,count(id) from logstg group by day;";
$result=mysql_query($sql,$con);
while($row = mysql_fetch_array($result))
{
$day[]=$row['day'];
$count[]=intval($row['count(id)']);
}
$day = json_encode($day);

$data1 = array(array("name"=>"count","data"=>$count));
$data1 = json_encode($data1); //把获取的数据对象转换成json格式

?>
