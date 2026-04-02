class Level {
	//TODO: consider using Uint32Array
	public tiles: Array<boolean>;
	public width: number;
	public height: number;

	constructor(width: number, height: number) {
		this.width = width;
		this.height = height;
		this.tiles = [];
		for (let i = 0; i < width * height; i++) {
			this.tiles.push(false);
		}
	}

	public get(x: number, y: number): boolean {
		return this.tiles[y * this.width + x];
	}

	public set(x: number, y: number, value: boolean) {
		this.tiles[y * this.width + x] = value;
	}
}