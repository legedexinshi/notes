<?php

include "libchart/libchart/classes/libchart.php";

$chart = new PieChart(500, 250);

	$dataSet = new XYDataSet();
		$dataSet->addPoint(new Point("Mozilla Firefox (80)", 80));
			$dataSet->addPoint(new Point("Konqueror (75)", 75));
				$dataSet->addPoint(new Point("Other (50)", 50));
					$chart->setDataSet($dataSet);

	$chart->setTitle("User agents for www.example.com");
		$chart->render("generated/demo3.png");
?>
