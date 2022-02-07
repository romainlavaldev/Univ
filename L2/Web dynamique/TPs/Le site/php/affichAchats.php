<?php
if(isset($_POST['avalider'])){
	if(!empty($_POST['alogin'])){
		$con = mysqli_connect('info.univ-lemans.fr', 'l2infoetu', 'webdyn72', 'l2info');
		if(!$con){
			echo 'Y\'a eu un problème dans l\'équation !';
		}else{
			$res = mysqli_query($con,"select nom from utilisateurs where login = \"" . $_POST['alogin'] . "\"");
			$res = mysqli_fetch_array($res);
			if(empty($res[0])){
				echo 'Il existe pas le gars !';			
			}else{
				$query = "select produit, quantite from achats where login = \"" . $_POST['alogin'] . "\"";
				$res = mysqli_query($con,$query);
				echo $_POST['alogin'] . " à acheté : ";
				while($data = mysqli_fetch_array($res)){
					echo $data[1] . " " . $data[0] . ", ";
				}
			}
		}
	}else{
	echo 'Faut remplir tous les champs quand même ...';
	}
}
else echo 'C\'est pas bien là';
?>
