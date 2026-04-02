enum Mode {
	Add = 0,
	Remove
}

interface Point {
	x: number;
	y: number;
}

class Draw {
	private canvas: HTMLCanvasElement;
	private ctx: CanvasRenderingContext2D;
	private level: Level;
	private tileSize: number;
	private strokeWidth: number;
	private tileColor: string;
	private strokeColor: string;
	private bgColor: string;

	private mouseHeld = false;
	private mode: Mode = Mode.Add;

	constructor(canvas: HTMLCanvasElement, level: Level, tileSize: number, strokeWidth: number, tileColor: string, strokeColor: string, bgColor: string) {
		this.canvas = canvas;
		this.ctx = canvas.getContext("2d");
		this.level = level;

		this.tileSize = tileSize;
		this.strokeWidth = strokeWidth;
		this.tileColor = tileColor;
		this.strokeColor = strokeColor;
		this.bgColor = bgColor;
	}

	/**
	 * Attaches event listeners to canvas
	 */
	public attachListeners() {
		this.canvas.addEventListener("mousedown", this.onMouseDown.bind(this));
		this.canvas.addEventListener("mouseup", this.onMouseUp.bind(this));
		this.canvas.addEventListener("mousemove", this.onMouseMove.bind(this));
	}

	public setLevel(level: Level) {
		this.level = level;
	}

	/**
	 * Redraws the level completely, including changing the canvas size
	 */
	public redraw() {
		this.canvas.width = this.tileSize * this.level.width;
		this.canvas.height = this.tileSize * this.level.height;

		this.ctx.strokeStyle = this.strokeColor;
		this.ctx.lineWidth = this.strokeWidth;

		for (let x = 0; x < this.level.width; x++) {
			for (let y = 0; y < this.level.height; y++) {
				this.drawTile(x, y);
			}
		}
	}

	/**
	 * Using current drawing mode, changes tile state and redraws if necessary
	 * @param x 	tile x
	 * @param y 	tile y
	 */
	private updateTile(x: number, y: number) {
		const isWall = this.level.get(x, y);
		const addWall = (this.mode == Mode.Add);

		if (isWall != addWall) {
			this.level.set(x, y, !isWall);
			this.drawTile(x, y);
		}
	}

	/**
	 * Draw the given tile onto the canvas
	 * @param x 	tile x
	 * @param y 	tile y
	 */
	private drawTile(x: number, y: number) {
		this.ctx.fillStyle = this.bgColor;
		if (this.level.get(x, y)) {
			this.ctx.fillStyle = this.tileColor;
		}

		this.ctx.fillRect(x * this.tileSize, y * this.tileSize, this.tileSize, this.tileSize);
		this.ctx.strokeRect(x * this.tileSize, y * this.tileSize, this.tileSize, this.tileSize);
	}

	/**
	 * Converts mouse coordinates to tile coordinates
	 * @param x 	mouse x
	 * @param y 	mouse y
	 * @returns 	Point
	 */
	private getTileCoordinates(x: number, y: number): Point {
		return {
			x: Math.floor(x / this.tileSize),
			y: Math.floor(y / this.tileSize)
		};
	}

	private onMouseDown(e: MouseEvent) {
		this.mouseHeld = true;

		const coords = this.getTileCoordinates(e.offsetX, e.offsetY);
		if (this.level.get(coords.x, coords.y)) {
			this.mode = Mode.Remove;
		} else {
			this.mode = Mode.Add;
		}

		this.updateTile(coords.x, coords.y);
	}

	private onMouseUp(e: MouseEvent) {
		this.mouseHeld = false;
	}

	private onMouseMove(e: MouseEvent) {
		//TODO: use Bresenham's agorithm
		if (this.mouseHeld) {
			const coords = this.getTileCoordinates(e.offsetX, e.offsetY);
			this.updateTile(coords.x, coords.y);
		}
	}
}