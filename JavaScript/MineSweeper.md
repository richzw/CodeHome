Source: http://code.tutsplus.com/tutorials/build-a-minesweeper-game-within-200-lines-of-code--active-8578

```
package  {
    import flash.display.Sprite;
    import flash.events.MouseEvent;
    public class Main extends Sprite {
        public var zones:Array;
        public var board:Sprite;
        public var boardWidth:int;
        public var boardHeight:int;
        public var numberOfMines:int;
        public function Main() {    //constructor----
            zones = new Array();
            board = new Sprite();
            boardWidth = 15;
            boardHeight = 15;
            numberOfMines = 30;
            gameover_btn.visible = false;
            again_btn.visible = false;
            minesleft_txt.text = String(numberOfMines);
            addChildAt(board, 0);
            createBoard();
            placeMines();
            placeNumbers();
            again_btn.addEventListener(MouseEvent.CLICK, makeAnotherGame);
        }   //end of constructor
        private function createBoard():void{
            for(var i:Number = 0; i < boardHeight; i++){
                var hzones:Array = new Array();
                zones[i] = hzones;
                for(var j:Number = 0; j < boardWidth; j++){
                    var newzone:Zone = new Zone(j, i);
                    zones[i][j] = newzone;
                    board.addChild(zones[i][j]);
                    zones[i][j].x = j*40 + 20;
                    zones[i][j].y = i*40 + 20;
                }
            }
        }
        private function placeMines():void{
            var bombsCounter:uint = numberOfMines;
            while(bombsCounter > 0){
                var randomNumber:Number = Math.round(Math.random()* ((boardHeight * boardWidth) - 1));
                var rowCount:Number = Math.floor(randomNumber / boardWidth);
                var columnCount:Number = randomNumber % boardWidth;
                if(!zones[rowCount][columnCount].state){
                    zones[rowCount][columnCount].state = true;
                    bombsCounter--;
                }
            }
        }
        private function placeNumbers():void{
            var zoneNumber:int = 0;
            for(var e:Number = 0; e < boardHeight; e++){
                for(var f:Number = 0; f < boardWidth; f++){
                    var zoneNeighbours:Array = getNeighbours(zones[e][f]);
                    var len:uint = zoneNeighbours.length;
                    zoneNumber = 0;         //resetting the value for each zone
                    for(var d:Number = 0; d < len; d++){
                        if(zoneNeighbours[d].state){ zoneNumber++; }
                    }
                    zones[e][f].num_txt.text = String(zoneNumber);
                    zones[e][f].zoneValue = zoneNumber;
                    if(zoneNumber == 0 || zones[e][f].state == true){
                        zones[e][f].num_txt.visible = false;
                    }
                }
            }
        }
        public function getNeighbours(z:Zone):Array{
            var neighboursArray:Array = [];
            if(z.ycor == 0){
            neighboursArray.push(zones[z.ycor + 1][z.xcor]);                //bottom center
                if(z.xcor == 0){                        //three surrounding zones
                    neighboursArray.push(zones[z.ycor][z.xcor + 1]);        //middle right
                    neighboursArray.push(zones[z.ycor + 1][z.xcor + 1]);    //bottom right
                } else if(z.xcor == (boardWidth - 1)){  //three surrounding zones
                    neighboursArray.push(zones[z.ycor][z.xcor - 1]);        //middle left
                    neighboursArray.push(zones[z.ycor + 1][z.xcor - 1]);    //bottom left
                } else{                                 //five surrounding zones
                    neighboursArray.push(zones[z.ycor][z.xcor - 1]);        //middle left
                    neighboursArray.push(zones[z.ycor][z.xcor + 1]);        //middle right
                    neighboursArray.push(zones[z.ycor + 1][z.xcor - 1]);    //bottom left
                    neighboursArray.push(zones[z.ycor + 1][z.xcor + 1]);    //bottom right
                }
            } else if(z.ycor == (boardHeight - 1)){
            neighboursArray.push(zones[z.ycor - 1][z.xcor]);                //top center
                if(z.xcor == 0){                        //three surrounding zones
                    neighboursArray.push(zones[z.ycor - 1][z.xcor + 1]);    //top right
                    neighboursArray.push(zones[z.ycor][z.xcor + 1]);        //middle right
                } else if(z.xcor == (boardWidth - 1)){  //three surrounding zones
                    neighboursArray.push(zones[z.ycor - 1][z.xcor - 1]);    //top left
                    neighboursArray.push(zones[z.ycor][z.xcor - 1]);        //middle left
                } else{                                 //five surrounding zones
                    neighboursArray.push(zones[z.ycor - 1][z.xcor - 1]);    //top left
                    neighboursArray.push(zones[z.ycor - 1][z.xcor + 1]);    //top right
                    neighboursArray.push(zones[z.ycor][z.xcor - 1]);        //middle left
                    neighboursArray.push(zones[z.ycor][z.xcor + 1]);        //middle right
                }
            } else {
            neighboursArray.push(zones[z.ycor - 1][z.xcor]);                //top center
            neighboursArray.push(zones[z.ycor + 1][z.xcor]);                //bottom center
                if(z.xcor == 0){                        //five surrounding zones
                    neighboursArray.push(zones[z.ycor - 1][z.xcor + 1]);    //top right
                    neighboursArray.push(zones[z.ycor][z.xcor + 1]);        //middle right
                    neighboursArray.push(zones[z.ycor + 1][z.xcor + 1]);    //bottom right
                } else if(z.xcor == (boardWidth - 1)){  //five surrounding zones
                    neighboursArray.push(zones[z.ycor - 1][z.xcor - 1]);    //top left
                    neighboursArray.push(zones[z.ycor][z.xcor - 1]);        //middle left
                    neighboursArray.push(zones[z.ycor + 1][z.xcor - 1]);    //bottom left
                } else{                                 //eight surrounding zones
                    neighboursArray.push(zones[z.ycor - 1][z.xcor - 1]);    //top left
                    neighboursArray.push(zones[z.ycor - 1][z.xcor + 1]);    //top right
                    neighboursArray.push(zones[z.ycor][z.xcor - 1]);        //middle left
                    neighboursArray.push(zones[z.ycor][z.xcor + 1]);        //middle right
                    neighboursArray.push(zones[z.ycor + 1][z.xcor - 1]);    //bottom left
                    neighboursArray.push(zones[z.ycor + 1][z.xcor + 1]);    //bottom right
                }
            }
            return neighboursArray;
        }
        private function makeAnotherGame(event:MouseEvent):void{
            gameover_btn.visible = false;
            again_btn.visible = false;
            removeChild(board);
            board = new Sprite();
            addChildAt(board, 0);
            zones = new Array();
            createBoard();
            placeMines();
            placeNumbers();
            minesleft_txt.text = String(numberOfMines);
        }
    }   //end of class
}   //end of package

```

---------------------------


```
package{
    import flash.display.MovieClip;
    import flash.events.MouseEvent;
    public class Zone extends MovieClip{
        public var state:Boolean;       //true contains mine, false not containing mine
        public var revealed:Boolean;
        public var marked:Boolean;
        public var xcor:uint;
        public var ycor:uint;
        public var zoneValue:int;
        public function Zone(corx:uint, cory:uint){
            this.state = false;
            this.revealed = false;
            this.marked = false;
            this.zoneValue = 0;
            this.xcor = corx;
            this.ycor = cory;
            this.highlight_mc.visible = false;
            this.bomb_mc.visible = false;
            this.addEventListener(MouseEvent.MOUSE_OVER, showHighlight);
            this.addEventListener(MouseEvent.MOUSE_OUT, removeHighlight);
            this.addEventListener(MouseEvent.CLICK, zoneClicked);
        }   //end of constructor
        private function showHighlight(event:MouseEvent):void{
            this.highlight_mc.visible = true;
        }
        private function removeHighlight(event:MouseEvent):void{
            this.highlight_mc.visible = false;
        }
        private function zoneClicked(event:MouseEvent):void{
            if(event.shiftKey){     //resemble right clicking
                if(this.marked){
                    this.bomb_mc.visible = false;
                    this.marked = false;
                this.parent.parent.minesleft_txt.text = String(int(this.parent.parent.minesleft_txt.text) + 1);
                } else{
                    this.bomb_mc.visible = true;
                    this.marked = true;
                    this.parent.parent.minesleft_txt.text = String(int(this.parent.parent.minesleft_txt.text) - 1);
                }
            } else{             //normal left clicking
                if(!state){
                    openZone();
                } else{             //game over ----
                    if(!this.marked){
                        this.parent.parent.gameover_btn.visible = true;
                        this.parent.parent.again_btn.visible = true;
                    }
                }
            }
        }
        private function openZone(){
            if(!this.marked && !this.revealed){
                this.block_mc.visible = false;
                this.revealed = true;
                this.highlight_mc.visible = false;
                this.removeEventListener(MouseEvent.MOUSE_OVER, showHighlight);
                this.removeEventListener(MouseEvent.MOUSE_OUT, removeHighlight);
                this.removeEventListener(MouseEvent.CLICK, zoneClicked);
                if(this.zoneValue == 0){ openNeighbours(); }
            }
        }
        private function openNeighbours():void{
            var neighbours:Array = this.parent.parent.getNeighbours(this);
            for(var h:Number = 0; h < neighbours.length; h++){
                if(!neighbours[h].revealed){ neighbours[h].openZone(); }
            }
        }
    }   //end of class
}   //end of package

```

