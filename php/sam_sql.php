<?php  

	$mysqli = new mysqli('127.0.0.1', 'root', '123');
	if($mysqli -> connect_error) {
		die('Error: ('. $mysqli->connect_errno .') '. $mysqli->connect_error);
	}
	$mysqli -> select_db('test');
/*
	$results = $mysqli->query("SELECT id, ss FROM tt");
	print '<table border="1">';
	while($row = $results->fetch_assoc()) {
	    print '<td>'.$row["id"].'</td>';
	    print '<td>'.$row[ss].'</td>';
	    print '</tr>';
	}  
*/
	$query = "SELECT id, ss FROM tt";
	$result = $mysqli -> query($query);

	if(!$result) echo fail;
	while(list($id, $ss) = $result->fetch_row()) 
		printf("%d, %d\n", $id, $ss);
	
	echo $result->affected_rows;

?>

