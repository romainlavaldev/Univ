<?php session_start(); if(isset($_POST['validerDeco'])) session_destroy();
header("Location: ../index.php"); ?>
