//FIXME: rename to map, to be consistent with server

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

	public toHexString(): string {
		let result: Array<string> = [];
		let hex = 0;
		let shift = 3;

		for (let i = 0; i < this.width * this.height; i++) {
			let value = this.tiles[i] ? 1 : 0;
			hex = hex | (value << shift);

			shift--;
			if (shift < 0) {
				result.push(hex.toString(16));
				shift = 3;
				hex = 0;
			}
		}

		//add trailing bits
		if (shift != 3) {
			result.push(hex.toString(16));
		}

		return result.join("");
	}
}