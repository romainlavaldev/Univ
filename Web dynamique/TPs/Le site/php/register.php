<?php

include('Dbconnect.php');

if(isset($_POST['rvalider'])){
	if(!empty($_POST['rlogin']) && !empty($_POST['rpass']) && !empty($_POST['rage']) && !empty($_POST['rnom']) && !empty($_POST['rprenom']) && !empty($_POST['remail'])){
		register($_POST['rnom'],$_POST['rprenom'],$_POST['rage'],$_POST['rlogin'],$_POST['rpass'],$_POST['remail']);
	}
	else{
	echo 'Faut remplir tous les champs quand même ...';
	}
}
else echo 'C\'est pas bien là';
?>

