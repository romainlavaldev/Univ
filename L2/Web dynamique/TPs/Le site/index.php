<?php session_start(); ?>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" />
        <meta name="description" content="" />
        <meta name="author" content="" />
        <title>Web Dynamique - Romain Laval</title>
        <link rel="icon" type="image/x-icon" href="assets/img/favicon.ico" />
        <!-- Font Awesome icons (free version)-->
        <script src="https://use.fontawesome.com/releases/v5.13.0/js/all.js" crossorigin="anonymous"></script>
        <!-- Google fonts-->
        <link href="https://fonts.googleapis.com/css?family=Varela+Round" rel="stylesheet" />
        <link href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i" rel="stylesheet" />
        <!-- Core theme CSS (includes Bootstrap)-->
        <link href="css/styles.css" rel="stylesheet" />
    </head>
    <body id="page-top">
        <!-- Navigation-->
        <nav class="navbar navbar-expand-lg navbar-light fixed-top" id="mainNav">
            <div class="container">
                <a class="navbar-brand js-scroll-trigger" href="#page-top"><?php if (isset($_SESSION['prenom']) && !empty($_SESSION['prenom'])) {
                	echo "Vous êtes " . $_SESSION['prenom'] . " !";
                }else echo "Vous n'êtes personne"; ?></a>
                <?php if (isset($_SESSION['prenom']) && !empty($_SESSION['prenom'])) echo '<form action="php/sessionDestroy.php" method="post">
                    <button type="submit" name="validerDeco">Deco</button>
                </form>'?>
                <button class="navbar-toggler navbar-toggler-right" type="button" data-toggle="collapse" data-target="#navbarResponsive" aria-controls="navbarResponsive" aria-expanded="false" aria-label="Toggle navigation">
                    Menu
                    <i class="fas fa-bars"></i>
                </button>
                <div class="collapse navbar-collapse" id="navbarResponsive">
                    <ul class="navbar-nav ml-auto">
                        <li class="nav-item"><a class="nav-link js-scroll-trigger" href="#about">About</a></li>
                        <li class="nav-item"><a class="nav-link js-scroll-trigger" href="#projects">Projects</a></li>
                        <li class="nav-item"><a class="nav-link js-scroll-trigger" href="#signup">Contact</a></li>
                    </ul>
                </div>
            </div>
        </nav>
        <!-- About-->
        <section class="about-section text-center" id="about">
		  <div class="row">
                    <div class="col-lg-8 mx-auto">
			<h2 class="text-white mb-4">Les pages de fou</h2>
			<a href="control.php">Eval 1</a>
      <a href="php/exo1mysqli.php">Zone SQL</a>
      <a href="php/repas.php">Miam</a>
			<h2 class="text-white mb-4">Calculateur de tables</h2>
			<form action="./php/table.php" method="POST">
				<input type="number" name="min">Min</input>
				<input type="number" name="max">Max</input>
				<input type="submit" name="valider" value="Valider"/>
			</form>
			<br><br>
			<h2 class="text-white mb-4">Convertisseur</h2>
			<form action="./php/convertisseur.php" method="GET">
				<input type="text" name="somme"/>
				<select name="deviseDepart">
					<option value="eu">Euro</option>
					<option value="us">Dollars US</option>
					<option value="ca">Dollars Canadien</option>
				</select>
				<h2 class="text-white"> Vers </h2>
				<select name="deviseArrive">
					<option value="eu">Euro</option>
					<option value="us">Dollars US</option>
					<option value="ca">Dollars Canadien</option>
				</select>
				<input type="submit" name="valider" value="Valider"/>
			</form>
		    </div>
		  </div>
		<?php

		if (preg_match("/mozilla/i",$_SERVER['HTTP_USER_AGENT'])){
			$class="mozilla";
		}
		else{
			$class="notMozilla";
		}

		for ($i = 1; $i<=10; $i++){


			echo '<div class="'. $class .'"><div class="col-lg-8 mx-auto">';
			echo '<h2>';
			echo "Table de " . $i;
			echo '<ul>';
			for ($j = 0; $j <=10; $j++){
				echo "<li>" . $i . "*" . $j . " = " . $i*$j . "</li>";
			}
			echo '</ul>';

			echo "</div> </div>";
		}


	    ?>
                <img class="img-fluid" src="assets/img/ipad.png" alt="" />
            </div>



        </section>

        <!-- Signup-->
        <section class="signup-section" id="signup">
            <div class="container">
                <div class="row">
                    <div class="col-md-10 col-lg-8 mx-auto text-center">
                        <i class="far fa-paper-plane fa-2x mb-2 text-white"></i>
                        <h2 class="text-white mb-5">Subscribe to receive updates!</h2>
                        <form class="form-inline d-flex" action="php/sendMail.php" method="POST">
                            <input class="form-control flex-fill mr-0 mr-sm-2 mb-3 mb-sm-0" id="inputEmail" name="sujet" type="text" placeholder="Sujet" />
			    <textarea class="" name="corp" rows="20" cols="69" ></textarea>
                            <button class="btn btn-primary mx-auto" type="submit" name="valider">Envoyer</button>
                        </form>
                    </div>
                </div>
            </div>
        </section>
        <!-- Bootstrap core JS-->
        <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.bundle.min.js"></script>
        <!-- Third party plugin JS-->
        <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.4.1/jquery.easing.min.js"></script>
        <!-- Core theme JS-->
        <script src="js/scripts.js"></script>
    </body>
</html>
