import scala.collection.mutable.ArrayBuffer

object Main{

    val max = 100 //Tamanho máximo do vetor auxliar que irá armazenar a contagem

    def coutingSort(vet: ArrayBuffer[Int]): Unit = {
        
        //incializando vetor auxiliar
        val aux = ArrayBuffer[Int]();
        for(i <- 0 to max) aux += 0

        //Contando
        for(i <- vet) aux(i) += 1

        //Reatribuindo intens ao vetor original de forma ordenada 
        vet.clear
        for(i <- 0 to max){
            for(j <- 0 until aux(i)) vet += i
        }
    }

    def main(args: Array[String]): Unit = {

        //Exemplo
        val vet = ArrayBuffer(4,5,2,7,6,1,9,8,3)
        coutingSort(vet)
        println(vet)
    }

}