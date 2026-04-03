//html elements
let mainCanvas: HTMLCanvasElement;
let widthInput: HTMLInputElement;
let heightInput: HTMLInputElement;
let generateButton: HTMLButtonElement;
let genGreedyNavMeshButton: HTMLButtonElement;

let ctx: CanvasRenderingContext2D;

let level: Level;
let draw: Draw;

const sendRequest = <T>(url: string, method: string, data?: any) => {
	return new Promise<T>((resolve, reject) => {
		const xhr = new XMLHttpRequest();
		xhr.addEventListener("load", (e) => {
			const response: T = JSON.parse(xhr.response);
			console.log(response);
			resolve(response);
		});
		xhr.open(method, url);
		if (method == "POST") {
			xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
			xhr.send(JSON.stringify(data));
		} else {
			xhr.send();
		}
	});
};

window.addEventListener("load", () => {

	//TODO: use something like Petite-Vue or Preact

	//fetch html elements
	mainCanvas = <HTMLCanvasElement>document.getElementById("mainCanvas");
	widthInput = <HTMLInputElement>document.getElementById("widthInput");
	heightInput = <HTMLInputElement>document.getElementById("heightInput");
	generateButton = <HTMLButtonElement>document.getElementById("generateButton");
	genGreedyNavMeshButton = <HTMLButtonElement>document.getElementById("genGreedyNavMeshButton");

	//attach event listeners
	draw = new Draw(mainCanvas, level, 16, 2, "#404040", "#e0ffe0", "#c0c0c0");
	draw.attachListeners();

	generateButton.addEventListener("click", () => {
		const width = widthInput.valueAsNumber;
		const height = heightInput.valueAsNumber;
		level = new Level(width, height);
		draw.setLevel(level);
		draw.redraw();
	});

	genGreedyNavMeshButton.addEventListener("click", () => {
		sendRequest("navmesh", "POST", {
			level: {
				width: level.width,
				height: level.height,
				tiles: level.toHexString()
			},
			algorithm: 0
		});
	});

	ctx = mainCanvas.getContext("2d");
});