/*
  runnen met:
  node main.js
*/

class Point {
  constructor(x, y, z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }

  toString(){
    return this.x + " " + this.y + " " + this.z;
  }
}
class Triangle {
  constructor(point1, point2, point3) {
    this.point1 = point1;
    this.point2 = point2;
    this.point3 = point3;
  }

  min_x() {return Math.min(this.point1.x,this.point2.x,this.point3.x);}
  min_y() {return Math.min(this.point1.y,this.point2.y,this.point3.y);}
  min_z() {return Math.min(this.point1.z,this.point2.z,this.point3.z);}

  max_x() {return Math.max(this.point1.x,this.point2.x,this.point3.x);}
  max_y() {return Math.max(this.point1.y,this.point2.y,this.point3.y);}
  max_z() {return Math.max(this.point1.z,this.point2.z,this.point3.z);}

  toString(){
    return this.point1.toString() + " " + this.point2.toString() + " " + this.point3.toString();
  }
}

let input = "bunny.mesh", output = "output.mesh";
let result = "";

let fs = require('fs'), path = require('path');

function readFile(input){
  let filePath = path.join(__dirname, input);
  return fs.readFileSync(filePath,'utf8');
}

function writeFile(name, text){
  let filePath = path.join(__dirname, name);
  fs.appendFile(name, text, (err) => {});
}
function clearFile(name){
  let filePath = path.join(__dirname, name);
  fs.writeFile(name, "", (err) => {});
}

function lowest_x(triangles){
  let result = triangles[0].min_x()
  for (let triangle of triangles){
    if (triangle.min_x() < result){
      result = triangle.min_x();
    }
  }
  return result
}
function lowest_y(triangles){
  let result = triangles[0].min_y()
  for (let triangle of triangles){
    if (triangle.min_y() < result){
      result = triangle.min_y();
    }
  }
  return result
}
function lowest_z(triangles){
  let result = triangles[0].min_z()
  for (let triangle of triangles){
    if (triangle.min_z() < result){
      result = triangle.min_z();
    }
  }
  return result
}

function highest_x(triangles){
  let result = triangles[0].max_x()
  for (let triangle of triangles){
    if (triangle.max_x() > result){
      result = triangle.max_x();
    }
  }
  return result
}
function highest_y(triangles){
  let result = triangles[0].max_y()
  for (let triangle of triangles){
    if (triangle.max_y() > result){
      result = triangle.max_y();
    }
  }
  return result
}
function highest_z(triangles){
  let result = triangles[0].max_z()
  for (let triangle of triangles){
    if (triangle.max_z() > result){
      result = triangle.max_z();
    }
  }
  return result
}

let textArray = readFile(input).split('\n');

let point_count = textArray[0];
textArray.splice(0, 1);

let points = [];
for (i = 0;i < point_count;i++) {
  let coords = textArray[i].split(' ');
  let point = new Point(coords[0],coords[1],coords[2]);
  points[i] = point;
}

textArray.splice(0, point_count);
let triangle_count = textArray[0];
textArray.splice(0, 1);

let triangles = [];
for (i = 0;i < triangle_count;i++){
  let triangle_points = textArray[i].split(' ');
  let triangle = new Triangle(points[triangle_points[0]],points[triangle_points[1]],points[triangle_points[2]]);
  triangles[i] = triangle;
}

function x_in_box(triangle, min, max){return (triangle.min_x() > min) && (triangle.max_x() < max);}
function y_in_box(triangle, min, max){return (triangle.min_y() > min) && (triangle.max_y() < max);}
function z_in_box(triangle, min, max){return (triangle.min_z() > min) && (triangle.max_z() < max);}

function write_box(triangles){
  for (let triangle of triangles) {
    result += "triangle " + triangle.toString() + "\n";
  }
  result += "box " + triangles.length + "\n";
}

function create_box_structure(triangles){
  if(triangles.length > 2){
    let x_width = highest_x(triangles) - lowest_x(triangles);
    let y_width = highest_y(triangles) - lowest_y(triangles);
    let z_width = highest_z(triangles) - lowest_z(triangles);
    let first = [], second = [];

    if (Math.max(x_width, y_width, z_width) == x_width){
      min_x = lowest_x(triangles);
      center_x = min_x + (x_width / 2);
      for (triangle of triangles){
        x_in_box(triangle, min_x, center_x) ? first.push(triangle) : second.push(triangle);
      }
    }
    else if (Math.max(x_width, y_width, z_width) == y_width) {
      min_y = lowest_y(triangles);
      center_y = min_y + (y_width / 2);
      for (triangle of triangles){
        y_in_box(triangle, min_y, center_y) ? first.push(triangle) : second.push(triangle);
      }
    }
    else if (Math.max(z_width, z_width, z_width) == z_width){
      min_z = lowest_z(triangles);
      center_z = min_z + (z_width / 2);
      for (triangle of triangles){
        z_in_box(triangle, min_z, center_z) ? first.push(triangle) : second.push(triangle);
      }
    }

    if(first.length == 0){
      let loop_length = Math.floor(second.length/2);
      let copyofsecond = second.slice();
      for (let i = 0;i < loop_length;i++) {
        first.push(copyofsecond[0]);
        second.splice(0,1);
      }
    }

    create_box_structure(first);
    create_box_structure(second);
    result += "box 2\n";
  }
  else if (triangles.length > 0) {
    write_box(triangles);
  }
}

clearFile(output);
create_box_structure(triangles);
result += "stop";
writeFile(output,result);
