let precedente = -1;
		let attente    = 0;
		let img;
		let imgp;

		function cachephotos () {
			img.style.visibility = 'hidden';
			imgp.style.visibility = 'hidden';
			attente = 0;
		}

		function clic (n) {
			if (attente != 1) {
				img = document.getElementById('img'+n);
				img.style.visibility = 'visible';
			    if (precedente<0) {
					precedente = n;
			    } else {
					imgp  = document.getElementById('img'+precedente);
					if (imgp.src==img.src) {
					} else {
						attente = 1;
						setTimeout('cachephotos();',800);
					}
					precedente = -1;
				}
			}
		}

		function initgame () {
			for (let i=1 ; i<=200 ; i++) {
				let n1    = Math.ceil(16*Math.random());
				let n2    = Math.ceil(16*Math.random());
				let img1  = document.getElementById('img'+n1);
				let img2  = document.getElementById('img'+n2);
				let src1  = img1.src;
				let src2  = img2.src;
				img1.src = src2;
				img2.src = src1;
			}
		}