import scala.collection.mutable.ArrayBuffer


object Main{

    def selectionSort(vet: ArrayBuffer[Int]):Unit = {

        for(i <- 0 until vet.length-1){
            var posMenor = i
            for(j <- i+1 until vet.length){
                if(vet(j) < vet(posMenor)){
                posMenor = j
                }
            }
            var temp = vet(i)
            vet(i) = vet(posMenor)
            vet(posMenor) = temp
        }
    }

    def main(args: Array[String]): Unit = {
        
        //Exemplo
        val vet = ArrayBuffer(3,5,7,1,2,8,4,6,9)
        selectionSort(vet)
        println(vet)

    }
   
  

}