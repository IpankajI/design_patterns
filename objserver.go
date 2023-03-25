package main

import "fmt"

type ISubject interface {
	Notify()
	AddObserver(IObserver)
	GetState() int
	SetState(int)
}

type Subject struct {
	state     int
	observers []IObserver
}

func (sbj *Subject) Notify() {
	for _, obj := range sbj.observers {
		obj.Update()
	}
}

func (sbj *Subject) GetState() int {

	return sbj.state
}

func (sbj *Subject) SetState(state int) {
	sbj.state = state
	sbj.Notify()
}

func (sbj *Subject) AddObserver(observer IObserver) {
	sbj.observers = append(sbj.observers, observer)
}

type IObserver interface {
	Update()
}

type DecimalObserver struct {
	subject ISubject
}

func (obs *DecimalObserver) Update() {
	fmt.Println(obs.subject.GetState())
}

func NewSubject() ISubject {
	return &Subject{
		observers: []IObserver{},
	}
}

func NewDecimalObserver(subject ISubject) IObserver {
	return &DecimalObserver{
		subject: subject,
	}
}

type BinaryObserver struct {
	subject ISubject
}

func (obs *BinaryObserver) Update() {
	fmt.Println(fmt.Sprintf("%b", obs.subject.GetState()))
}

func NewBinaryObserver(subject ISubject) IObserver {
	return &BinaryObserver{
		subject: subject,
	}
}

func main() {

	subject := NewSubject()
	subject.AddObserver(NewDecimalObserver(subject))
	subject.AddObserver(NewBinaryObserver(subject))
	subject.SetState(10)
}
