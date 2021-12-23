#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofSetCircleResolution(36);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	
	this->mesh.clear();
	this->circle_list.clear();
	
	vector<glm::vec2> location_list;
	for (int i = 0; i < 3; i++) {

		auto noise_seed = ofRandom(1000);
		for (int x = -360; x <= 360; x += 5) {

			auto location = glm::vec2(x, ofMap(ofNoise(noise_seed, x * 0.0065, ofGetFrameNum() * 0.0065), 0, 1, -200, 200));
			location_list.push_back(location);

			this->mesh.addVertex(glm::vec3(location, 3));
			if (x > -360) {

				this->mesh.addIndex(this->mesh.getNumVertices() - 1);
				this->mesh.addIndex(this->mesh.getNumVertices() - 2);
			}
		}
	}

	for (int i = 0; i < location_list.size(); i++) {

		this->circle_list.push_back(glm::vec3(location_list[i], 0));
		auto near_count = 0;
		for (int k = 0; k < location_list.size(); k++) {

			if (i == k) { continue; }

			auto distance = glm::distance(location_list[i], location_list[k]);
			if (distance < 15) {

				near_count++;
			}
		}

		this->circle_list.back().z = pow(1.5, near_count);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofSetColor(255);
	ofSetLineWidth(0.5);
	this->mesh.drawWireframe();
	
	ofNoFill();
	ofSetLineWidth(2);
	for (auto& circle : this->circle_list) {

		ofDrawCircle(glm::vec2(circle.x, circle.y), circle.z);
	}

	ofFill();
	ofSetColor(0);
	for (auto& circle : this->circle_list) {

		ofDrawCircle(glm::vec2(circle.x, circle.y), circle.z);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}