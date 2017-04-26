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
            $(function() {
                $('#highcharts').highcharts({
                    chart: {
                        renderTo: 'chart_pie', //饼状图关联html元素id值
                        defaultSeriesType: 'pie', //默认图表类型为饼状图
                        plotBackgroundColor: '#ffc', //设置图表区背景色
                        plotShadow: true   //设置阴影
                    },
                    title: {
                        text: ' '  //图表标题
                    },
                    credits: {
                        text: ' '
                    },
                    tooltip: {
                        formatter: function() { //鼠标滑向图像提示框的格式化提示信息
                            return '<b>' + this.point.name + '</b>: ' + twoDecimal(this.percentage) + ' %';
                        }
                    },
                    plotOptions: {
                        pie: {
                            allowPointSelect: true, //允许选中，点击选中的扇形区可以分离出来显示
                            cursor: 'pointer', //当鼠标指向扇形区时变为手型（可点击）
                            //showInLegend: true,  //如果要显示图例，可将该项设置为true
                            dataLabels: {
                                enabled: true, //设置数据标签可见，即显示每个扇形区对应的数据
                                color: '#000000', //数据显示颜色
                                connectorColor: '#999', //设置数据域扇形区的连接线的颜色
                                style: {
                                    fontSize: '12px'  //数据显示的大小
                                },
                                formatter: function() { //格式化数据
                                    return '<b>' + this.point.name;// + '</b>: ' + twoDecimal(this.percentage) + ' %';
                                }
                            }
                        }
                    },
                    series: [{//数据列
                            name: 'search engine',
                            data: data //核心数据列来源于php读取的数据并解析成JSON
                        }]
                });
            });

            function twoDecimal(x) { //保留2位小数
                var f_x = parseFloat(x);
                if (isNaN(f_x)) {
                    alert('错误的参数');
                    return false;
                }
                var f_x = Math.round(x * 100) / 100;
                var s_x = f_x.toString();
                var pos_decimal = s_x.indexOf('.');
                if (pos_decimal < 0) {
                    pos_decimal = s_x.length;
                    s_x += '.';
                }
                while (s_x.length <= pos_decimal + 2) {
                    s_x += '0';
                }
                return s_x;
            }
        </script>
    </body>
</html>

