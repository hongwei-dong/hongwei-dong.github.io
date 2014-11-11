//---------------preload--------------------
var load_state = {  
    preload: function() { 
	this.load.image('background', 'assets/background.png');
    this.load.image('ground', 'assets/ground.png');
	
        this.game.stage.backgroundColor = '#71c5cf';
     //   this.game.load.image('bird', 'assets/bird.png');  
	 this.load.spritesheet('bird', 'assets/bird.png', 50,35,3);//34,24,3);
        this.game.load.image('pipe', 'assets/pipe.png');  
        this.game.load.audio('jump', 'assets/jump.wav');
		
		
		this.game.load.image('pipeTop', 'assets/pipeT.png');  
		this.game.load.image('pipeBottom', 'assets/pipeB.png'); 		
    },

    create: function() {
        // When all assets are loaded, go to the 'menu' state
        this.game.state.start('menu');
    }	
};


//---------------menu--------------------
var menu_state = {
    create: function() {
        // Call the 'start' function when pressing the spacebar
        var space_key = this.game.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR);
        space_key.onDown.add(this.start, this); 
this.game.input.onDown.add(this.start, this);
		
	// ground	   
		this.background = this.game.add.sprite(0,0,'background');
		this.groundX = 0;
		this.ground = this.game.add.sprite(this.groundX,492, 'ground');
		this.ground2 = this.game.add.sprite(this.groundX+335,492, 'ground');
		this.ground3 = this.game.add.sprite(this.groundX+670,492, 'ground');
	
		this.ground.body.velocity.x = -200;
		this.ground2.body.velocity.x = -200;
		this.ground3.body.velocity.x = -200;

        // Defining variables
        var style = { font: "30px Arial", fill: "#ffffff" };
        var x = this.game.world.width/2, y = game.world.height/2;
		
        // Adding a text centered on the screen
        var text = this.game.add.text(x, y-50, "Press space or mouse to start", style);
        text.anchor.setTo(0.5, 0.5); 

        // If the user already played
        if (score > 0) {
            // Display its score
            var score_label = this.game.add.text(x, y-100, "score: " + score, style);
            score_label.anchor.setTo(0.5, 0.5); 
        }
		
    },
	
	update: function() {	   
        if(this.ground.x<-335){
		   if(this.ground2.x<this.ground3.x){
		      this.ground.x = this.ground3.x+335;
		   }
		   else this.ground.x = this.ground2.x+335;           
		}
		if(this.ground2.x<-335){
		   if(this.ground.x<this.ground3.x){
		      this.ground2.x = this.ground3.x+335;
		   }
		   else this.ground2.x = this.ground.x+335;           
		}
		if(this.ground3.x<-335){
		   if(this.ground.x<this.ground2.x){
		      this.ground3.x = this.ground2.x+335;
		   }
		   else this.ground3.x = this.ground.x+335;           
		}
		
	},

    // Start the actual game
    start: function() {
        this.game.state.start('play');
    }
};



//---------------play--------------------
var play_state = {

    // No more preload, since it is already done in the 'load' state

    create: function() { 
        var space_key = this.game.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR);
        space_key.onDown.add(this.jump, this); 
this.game.input.onDown.add(this.jump, this);

		this.background = this.game.add.sprite(0,0,'background');
		this.ground = this.game.add.sprite(0,492, 'ground');
		this.ground2 = this.game.add.sprite(335,492, 'ground');
		this.ground3 = this.game.add.sprite(670,492, 'ground');
	
		this.ground.body.velocity.x = -200;
		this.ground2.body.velocity.x = -200;
		this.ground3.body.velocity.x = -200;
	
	
        this.pipes = game.add.group();
        this.pipes.createMultiple(20, 'pipe');  
		
		this.pipesTop = game.add.group();
        this.pipesTop.createMultiple(4, 'pipeTop');  
		this.pipesBottom = game.add.group();
        this.pipesBottom.createMultiple(4, 'pipeBottom');  
		
        this.timer = this.game.time.events.loop(1500, this.add_row_of_pipes, this);   
	
		
        this.bird = this.game.add.sprite(100, 245, 'bird');
        this.bird.body.gravity.y = 1000; 
        this.bird.anchor.setTo(-0.2, 0.5);
    	
        // Not 'this.score', but just 'score'
        score = 0; 
        var style = { font: "30px Arial", fill: "#ffffff" };
        this.label_score = this.game.add.text(20, 20, "0", style); 

        this.jump_sound = this.game.add.audio('jump'); 		

    },

    update: function() {
	
	    if(this.bird.y>=492)  this.restart_game(); 
        if (this.bird.inWorld == false)
            this.restart_game(); 

        if (this.bird.angle < 20)
            this.bird.angle += 1;

        this.game.physics.overlap(this.bird, this.pipes, this.hit_pipe, null, this);  
		this.game.physics.overlap(this.bird, this.pipesTop, this.hit_pipe, null, this); 
		this.game.physics.overlap(this.bird, this.pipesBottom, this.hit_pipe, null, this);  

	    if(this.ground.x<-335){
		   if(this.ground2.x<this.ground3.x){
		      this.ground.x = this.ground3.x+335;
		   }
		   else this.ground.x = this.ground2.x+335;           
		}
		if(this.ground2.x<-335){
		   if(this.ground.x<this.ground3.x){
		      this.ground2.x = this.ground3.x+335;
		   }
		   else this.ground2.x = this.ground.x+335;           
		}
		if(this.ground3.x<-335){
		   if(this.ground.x<this.ground2.x){
		      this.ground3.x = this.ground2.x+335;
		   }
		   else this.ground3.x = this.ground.x+335;           
		}	
		
    },

    jump: function() {
        if (this.bird.alive == false)
            return; 

        this.bird.body.velocity.y = -350;
        this.game.add.tween(this.bird).to({angle: -20}, 100).start();
        this.jump_sound.play();
    },

    hit_pipe: function() {
        if (this.bird.alive == false)
            return;

        this.bird.alive = false;
        this.game.time.events.remove(this.timer);

        this.pipes.forEachAlive(function(p){
            p.body.velocity.x = 0;
        }, this);
		this.pipesTop.forEachAlive(function(p){
            p.body.velocity.x = 0;
        }, this);
		this.pipesBottom.forEachAlive(function(p){
            p.body.velocity.x = 0;
        }, this);
    },

    restart_game: function() {
        this.game.time.events.remove(this.timer);

        // This time we go back to the 'menu' state
        this.game.state.start('menu');
    },

    add_one_pipe: function(x, y) {
        var pipe = this.pipes.getFirstDead();
        pipe.reset(x, y);
        pipe.body.velocity.x = -200; 
        pipe.outOfBoundsKill = true;
    },
	add_one_pipe_top: function(x, y) {
        var pipe = this.pipesTop.getFirstDead();
		pipe.reset(x-2, y);
        pipe.body.velocity.x = -200; 
        pipe.outOfBoundsKill = true;
    },
	
	add_one_pipe_bottom: function(x, y) {
        var pipe = this.pipesBottom.getFirstDead();
        pipe.reset(x-2, y);
        pipe.body.velocity.x = -200; 
        pipe.outOfBoundsKill = true;
    },

    add_row_of_pipes: function() {
    	var toAdd = Math.floor(Math.random()*5);
		if(toAdd==0) return;
		
        var hole = Math.floor(Math.random()*5)+1;
       /* 
        for (var i = 0; i < 8; i++)
            if (i != hole && i != hole +1) 
                this.add_one_pipe(400, i*60+10);   
        */
		for (var i = 0; i < hole; i++)
            this.add_one_pipe(400, i*50+2);   
			
        this.add_one_pipe_top(400, hole*50+2);		
		this.add_one_pipe_bottom(400, (hole+4)*50-12-24);				
		
		for (var i = 9; i >hole+3; i--)
            this.add_one_pipe(400, i*50-12);   
			
        // Not 'this.score', but just 'score'
        score += 1; 
        this.label_score.content = score;  
    },
};

//--------------------temp---------------------------
//-------------------Initialize Phaser---------------
var game = new Phaser.Game(400, 490+112, Phaser.AUTO, 'game_div');

// Our 'score' global variable
var score = 0;

// Define all the states
game.state.add('load', load_state);  
game.state.add('menu', menu_state);  
game.state.add('play', play_state);  

// Start with the 'load' state
game.state.start('load');  