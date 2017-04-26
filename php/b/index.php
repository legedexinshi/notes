<?php
include_once('connect.php');
$res = mysql_query("select * from asd");
while ($row = mysql_fetch_array($res)) {
    if ($row['id'] == 1) {
        $arr1[] = array(
            "name" => $row['title'],
            "y" => intval($row['pv']),
            "sliced" => true,
            "selected" => true
        );
    } else {
        $arr[] = array(
            $row['title'], intval($row['pv'])
        );
    }
}
//合并数组
$arrs = array_merge($arr1, $arr);
$data = json_encode($arrs);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head> 
        <meta http-equivdddd="Content-Type" content="text/html; charset=utf-8" /> 
        <title> </title>
        <style>
            .demo{margin:50px auto}
            .myclass{border:1px solid #000; background:#ccc; color:#fff}
        </style>
    </head>
    <body>
        <div class="head">
        </div>
        <div id="container">
            <div class="demo" id="highcharts"></div>
		</div>
        <script type="text/javascript" src="http://www.sucaihuo.com/Public/js/other/jquery.js"></script>
        <script src="js/highcharts.js"></script>
        <script src="js/modules/exporting.js"></script>
        <script type="text/javascript">
            var data  = <?php echo $data;?>;

</script>
    </body>
</html>

