(function () {

  let FPS; 
  let gameDimensions = [1243, 930];
  let focoDimensions = [100, 130];
  let devastacaoDimensions = [100,100];
  let vidasDimensions = [65,34];
  let caveiraDimensions = [100,116];
  let menuDimensions = [1024,576];
  let containerDimensions = [1243,965];
  let focos;
  let numeroDeVidas = 5;
  let probFoco = 25;
  let score_value = 0;
  let status_atual = "g"; // (g) de game over, (s) de start, (p) de pause;
  let gameLoop;
  let vidasLoop;
  let reserva;
  let score_objetc;
  let vidas;
  let menu;
  let container;
  let dificuldadeLoop;
  
  
  function init() {
    dificuldadeLoop = setInterval(aumentaDificuldade,60000);
    vidasLoop = setInterval(perdeVida,2000);
    gameLoop = setInterval(run, 1000/FPS);
        
  }
 
  class Container{
    constructor(){
      this.element = document.createElement("div");
      this.element.className = "container";
      this.element.style.width = `${containerDimensions[0]}px`;
      this.element.style.height = `${containerDimensions[1]}px`;
      document.body.appendChild(this.element);
    }
  }

  class MenuStart{
    constructor(){
      this.element = document.createElement("div");
      this.element.className = "menu-start";
      this.element.style.width = `${menuDimensions[0]}px`;
      this.element.style.height = `${menuDimensions[1]}px`;
      container.element.appendChild(this.element);
    }

    apagaMenu(){
      container.element.removeChild(this.element);
    }
  }

  class MenuPause{
    constructor(){
      this.element = document.createElement("div");
      this.element.className = "menu-pause";
      this.element.style.width = `${menuDimensions[0]}px`;
      this.element.style.height = `${menuDimensions[1]}px`;
      container.element.appendChild(this.element);
    }

    apagaMenu(){
      container.element.removeChild(this.element);
    }
  }

  class MenuGameOver{
    constructor(){
      this.element = document.createElement("div");
      this.element.className = "menu-game-over";
      this.element.style.width = `${menuDimensions[0]}px`;
      this.element.style.height = `${menuDimensions[1]}px`;
      container.element.appendChild(this.element);
    }

    apagaMenu(){
      container.element.removeChild(this.element);
    }
  }

  class Reserva {
    constructor () {
      this.element = document.createElement("div");
      this.element.className = "reserva";
      this.element.style.width = `${gameDimensions[0]}px`;
      this.element.style.height = `${gameDimensions[1]}px`;
      container.element.appendChild(this.element);
    }

    apagaReserva(){
      container.element.removeChild(this.element);
    }
  }

  class FocoIncendio {
    constructor () {
      this.element = document.createElement("div");
      this.element.className = "foco-incendio";
      this.element.style.width = `${focoDimensions[0]}px`;
      this.element.style.height = `${focoDimensions[1]}px`;
      let left = Math.floor((Math.random() * (gameDimensions[0]-focoDimensions[0])));
      let top = Math.floor((Math.random() * (gameDimensions[1]-focoDimensions[1])));

      while(posicaoDosLagos(left,top)){
        left = Math.floor((Math.random() * (gameDimensions[0]-focoDimensions[0])));
        top = Math.floor((Math.random() * (gameDimensions[1]-focoDimensions[1])));
      }
      this.element.style.left = `${left}px`;
      this.element.style.top = `${top}px`;
      reserva.element.appendChild(this.element);
      
    }

    apagaFocoIcendio(){
      reserva.element.removeChild(this.element);
    }
    
    trocaImagem(){
      numeroDeVidas--;
      this.element.className = "devastacao";
      this.element.style.width = `${devastacaoDimensions[0]}px`;
      this.element.style.height = `${devastacaoDimensions[1]}px`;
    }
    
  }

  class CaveiraDeFogo{
    constructor(){
      this.element = document.createElement("div");
      this.element.className = "caveira-de-fogo";
      this.element.style.width = `${caveiraDimensions[0]}px`;
      this.element.style.height = `${caveiraDimensions[1]}px`;
      let left = Math.floor((Math.random() * (gameDimensions[0]-caveiraDimensions[0])));
      let top = Math.floor((Math.random() * (gameDimensions[1]-caveiraDimensions[1])));

      while(posicaoDosLagos(left,top)){
        left = Math.floor((Math.random() * (gameDimensions[0]-caveiraDimensions[0])));
        top = Math.floor((Math.random() * (gameDimensions[1]-caveiraDimensions[1])));
      }
      this.element.style.left = `${left}px`;
      this.element.style.top = `${top}px`;
      reserva.element.appendChild(this.element);
    }

    apagaFocoIcendio(){
      reserva.element.removeChild(this.element);
    }
    
    trocaImagem(){
      numeroDeVidas -= 2;
      this.element.className = "caveira-devastacao";
      this.element.style.width = `${devastacaoDimensions[0]}px`;
      this.element.style.height = `${devastacaoDimensions[1]}px`;
    }
  }

  class Vidas{
    constructor(){
      this.element = document.createElement("div");
      this.element.className = "vidas";
      this.element.style.width = `${vidasDimensions[0]*numeroDeVidas}px`;
      this.element.style.height = `${vidasDimensions[1]}px`;
      container.element.appendChild(this.element);
    }

    atualizaVidas(){
      if(numeroDeVidas > 0){
        this.element.style.width = `${vidasDimensions[0]*numeroDeVidas}px`;
      }else if(status_atual != "g"){
        status_atual = "g";
        this.element.style.width = `${vidasDimensions[0]*0}px`;
        menu = new MenuGameOver();
        clearInterval(gameLoop);
        clearInterval(vidasLoop);
        clearInterval(dificuldadeLoop);
      }
      
    }
  }

  class Score{
    constructor(){
      this.element = document.createElement("div");
      this.element.className = "score";
      this.element.innerHTML = score_value.toString().padStart(5,"0");
      container.element.appendChild(this.element);
      
    }

    atualizaScore(){
      this.element.innerHTML = score_value.toString().padStart(5,"0");
    }
  }

  function run () {
    if(Math.random() * 100 < probFoco) {
      let foco = new FocoIncendio();
      focos.push(foco);
             
    }else if(Math.random()*100 < probFoco/4){
      let caveira = new CaveiraDeFogo();
      focos.push(caveira);
    }
  }

  function perdeVida(){
    if(focos.length > 0){
      focos[0].trocaImagem();
      vidas.atualizaVidas();
      focos.splice(focos.indexOf(focos[0]), 1);
    }
  }

  function posicaoDosLagos(left,top){
    if((left > 590 && left < 1104 && top > 0 && top < 124) || (left > 1 && left < 253 && top > 436 && top < 726)){
      return 1;
    }
    return 0;
  }

  function aumentaDificuldade(){
    FPS++;
    clearInterval(dificuldadeLoop);
    clearInterval(vidasLoop);
    clearInterval(gameLoop);
    init();
    
  }

  document.body.addEventListener("mousedown", function (e) {
    if(status_atual === "s"){
      for(let i = 0; i < focos.length; i++){
        if(focos[i].element === e.path[0]){
          if(focos[i].element.className === "foco-incendio"){
            score_value += 10;
          }else{
            score_value += 25;
          }
          score_objetc.atualizaScore();
          focos[i].apagaFocoIcendio();
          focos.splice(focos.indexOf(focos[i]), 1);
          
        }
      }
    }
    
  })

  window.addEventListener("keydown", function (e) {
    if(e.key === 'p' && status_atual === "s") {
      status_atual = "p";      
      clearInterval(gameLoop);
      clearInterval(vidasLoop);
      clearInterval(dificuldadeLoop);
      menu = new MenuPause();
    }else if(e.key === 'r' && status_atual === "p"){
      status_atual = "s";
      menu.apagaMenu();
      init();
    }else if(e.key === 's' && status_atual === "g"){
      status_atual = "s";
      focos = [];
      FPS = 1;
      numeroDeVidas = 5;
      vidas.atualizaVidas();
      score_value = 0;
      score_objetc.atualizaScore();
      reserva.apagaReserva();
      reserva = new Reserva();
      menu.apagaMenu();
      init();
    }
  })

  container = new Container();
  reserva = new Reserva();
  vidas = new Vidas();
  score_objetc = new Score();
  menu = new MenuStart();
  
    
    
})();
