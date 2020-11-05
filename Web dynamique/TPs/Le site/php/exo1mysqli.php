<?php
	session_start();
 ?>

<html>
<a href="../index.php">retour</a>
<h2><?php if (isset($_SESSION['prenom']) && !empty($_SESSION['prenom'])) {
	echo "Vous êtes " . $_SESSION['prenom'] . " !";
}else echo "Vous n'êtes personne"; ?> </h2>
<br>
<br>
	<form action="DBUse.php" method="POST">
		<input type="text" name="nom">Nom</input><br/>
		<input type="text" name="prenom">Prénom</input><br/>
		<input type="text" name="login">Login</input><br/>
		<input type="password" name="pass">Mot de Passe</input><br/>
		<input type="submit" name="valider" value="Valider"/>
	</form>
<h2> INSCRIPTION </h2>
<form action="register.php" method="POST">
		<input type="text" name="rnom">Nom</input><br/>
		<input type="text" name="rprenom">Prénom</input><br/>
		<input type="number" name="rage">Age</input><br/>
		<input type="text" name="rlogin">Login</input><br/>
		<input type="password" name="rpass">Mot de Passe</input><br/>
		<input type="text" name="remail">Email</input><br/>
		<input type="submit" name="rvalider" value="Valider"/>
	</form>

<h2> ACHATS </h2>
	<form action="affichAchats.php" method="POST">
		<input type="text" name="alogin">Login</input><br/>
		<input type="submit" name="avalider" value="Voir ses achats !"/>
	</form>
</html>
